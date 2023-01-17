/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:35:27 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/15 19:14:46 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ext_no_perms(const char *exec_path)
{
	if (access(exec_path, X_OK) == -1)
	{
		perror("Error during execution of program: ");
		if (g_krsh.num_of_cmds > 1)
			exit(NO_EXECUTION_PERMISSION);
	}
}

/**
 * @brief			Find and execute commands from the PATH environment variable
 *
 * @param cmd		The command to be executed
 * @param argv		The parameters to the command
 * @param envp		Environment variables
 * @return int		Status code of execution (1 on SUCCESS, 0 on 'CMD NOT FOUND')
 */
int	search_absolute_path(char **argv)
{
	int		i;
	char	*exec_path;
	char	**paths;
	t_pair	*path;

	path = retrieve_from_dict(g_krsh.env_mngr, "PATH");
	if (!path || !path->value)
		return (EXIT_FAILURE);
	paths = ft_split(path->value, ':');
	i = 0;
	while (paths[i])
	{
		exec_path = ft_strjoin(ft_strjoin(paths[i], "/"), argv[0]);
		if (access(exec_path, F_OK) != -1 && execve(exec_path, argv,
				g_krsh.envp) == -1)
		{
			ext_no_perms(exec_path);
			return (ERROR_DURING_EXECUTION);
		}
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
 * @param cmd		The command to be executed
 * @param argv		The parameters to the command
 * @param envp		Environment variables
 * @return int		Status code of execution
 * 					(1 on SUCCESS, 0 on 'CMD NOT FOUND')
 */
int	search_relative_path(char **argv)
{
	if (ft_strchr(argv[0], '/') != 0 && execve(argv[0], argv, g_krsh.envp)
		== -1)
	{
		if (access(argv[0], X_OK) == -1)
		{
			perror("Error during execution: ");
			if (g_krsh.num_of_cmds > 1)
				exit(NO_EXECUTION_PERMISSION);
			g_krsh.status_code = NO_EXECUTION_PERMISSION;
			return (ERROR_COMMAND_NOT_FOUND);
		}
		perror("Error during execution: ");
		return (ERROR_DURING_EXECUTION);
	}
	return (EXIT_FAILURE);
}

t_bool	is_builtin(t_command *cmd)
{
	if (!cmd->argv || !cmd->argv[0])
		return (FALSE);
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		return (TRUE);
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (TRUE);
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (TRUE);
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		return (TRUE);
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (TRUE);
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		return (TRUE);
	if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		return (TRUE);
	return (FALSE);
}

int	exec_single_builtin(t_command *cmd)
{
	if (!cmd->next && is_builtin(cmd))
	{
		g_krsh.stdout_old = dup(STDOUT_FILENO);
		if (perform_io_redirections(cmd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (exec_builtin(cmd) == EXIT_SUCCESS)
		{
			dup2(g_krsh.stdout_old, STDOUT_FILENO);
			close(g_krsh.stdout_old);
			return (EXIT_SUCCESS);
		}
		dup2(g_krsh.stdout_old, STDOUT_FILENO);
		close(g_krsh.stdout_old);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
