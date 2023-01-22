/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 06:56:05 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/22 06:58:06 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ext_no_perms(const char *exec_path)
{
	if (access(exec_path, X_OK) == -1)
	{
		perror("No execution permissions: ");
		if (g_krsh.num_of_cmds > 1)
			exit_minishell(g_krsh.cmds, NO_EXECUTION_PERMISSION);
	}
	if (g_krsh.num_of_cmds > 1)
		exit_minishell(g_krsh.cmds, NO_EXECUTION_PERMISSION);
	g_krsh.status_code = NO_EXECUTION_PERMISSION;
}

static int	exec_env_path(int i, char **argv, char **paths, char *exec_path)
{
	if (access(exec_path, F_OK) != -1 && execve(exec_path, argv,
			g_krsh.envp) == -1)
	{
		while (paths[i])
			free(paths[i++]);
		ext_no_perms(exec_path);
		g_krsh.status_code = NO_EXECUTION_PERMISSION;
		free(exec_path);
		return (ERROR_DURING_EXECUTION);
	}
	return (EXIT_FAILURE);
}

/**
 * @brief			Find and execute commands from the PATH environment variable
 *
 * @param cmd		The command to be executed
 * @param argv		The parameters to the command
 * @param envp		Environment variables
 * @return int		Status code of execution (1 on SUCCESS, 0 on 'CMD NOT FOUND')
 */
static int	search_env_path(char **argv)
{
	int		i;
	char	*exec_path;
	char	**paths;
	t_pair	*path;

	path = retrieve_from_dict(g_krsh.env_mngr, "PATH");
	if (!path || !path->value || argv[0][0] == '/')
		return (EXIT_FAILURE);
	paths = ft_split(path->value, ':');
	i = 0;
	while (paths[i])
	{
		exec_path = join_and_free(ft_strjoin(paths[i], "/"), argv[0],
				TRUE, FALSE);
		if (exec_env_path(i, argv, paths, exec_path) == ERROR_DURING_EXECUTION)
			return (ERROR_DURING_EXECUTION);
		free(exec_path);
		free(paths[i]);
		i++;
	}
	free(paths);
	return (EXIT_FAILURE);
}

/**
 * @brief 			Find and execute commands based on current directory
 * 					(Eg. run executables)
 *
 * @param argv		The parameters to the command
 * @param envp		Environment variables
 * @return int		Status code of execution
 * 					(1 on SUCCESS, 0 on 'CMD NOT FOUND')
 */
static int	search_for_executable(char **argv)
{
	if (ft_strchr(argv[0], '/') != 0 && access(argv[0], F_OK) != -1)
	{
		if (access(argv[0], X_OK) == -1)
		{
			perror("No execution permission : ");
			if (g_krsh.num_of_cmds > 1)
				exit_minishell(g_krsh.cmds, NO_EXECUTION_PERMISSION);
			g_krsh.status_code = NO_EXECUTION_PERMISSION;
			return (NO_EXECUTION_PERMISSION);
		}
		if (execve(argv[0], argv, g_krsh.envp) == -1)
			perror("Error during execution : ");
		g_krsh.status_code = ERROR_DURING_EXECUTION;
		return (ERROR_DURING_EXECUTION);
	}
	return (EXIT_FAILURE);
}

void	ext_if_cmd_not_found(t_command *cmd)
{
	int	i;

	i = 0;
	while (i < g_krsh.heredoc_count)
	{
		close(g_krsh.heredocs[i][0]);
		close(g_krsh.heredocs[i][1]);
		free(g_krsh.heredocs[i]);
		i++;
	}
	if (g_krsh.heredoc_count > 0)
		free(g_krsh.heredocs);
	g_krsh.heredoc_count = 0;
	if (!cmd->argv[0][0] || (exec_builtin(cmd) == EXIT_FAILURE &&
		search_env_path(cmd->argv) == EXIT_FAILURE &&
		search_for_executable(cmd->argv) == EXIT_FAILURE))
	{
		write(STDERR_FILENO, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(STDERR_FILENO, " :Command not founddddd\n", 21);
		exit_minishell(g_krsh.cmds, ERROR_COMMAND_NOT_FOUND);
	}
}
