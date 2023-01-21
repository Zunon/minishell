/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:35:27 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/22 00:58:30 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ext_no_perms(t_command *cmd, const char *exec_path)
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

/**
 * @brief			Find and execute commands from the PATH environment variable
 *
 * @param cmd		The command to be executed
 * @param argv		The parameters to the command
 * @param envp		Environment variables
 * @return int		Status code of execution (1 on SUCCESS, 0 on 'CMD NOT FOUND')
 */
static int	search_env_path(t_command *cmd, char **argv)
{
	int		i;
	char	*exec_path;
	char	**paths;
	t_pair	*path;
	char	*temp;

	path = retrieve_from_dict(g_krsh.env_mngr, "PATH");
	if (!path || !path->value || argv[0][0] == '/')
		return (EXIT_FAILURE);
	paths = ft_split(path->value, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		exec_path = ft_strjoin(temp, argv[0]);
		if (access(exec_path, F_OK) != -1 && execve(exec_path, argv,
				g_krsh.envp) == -1)
		{
			free(exec_path);
			free(temp);
			while (paths[i])
				free(paths[i++]);
			ext_no_perms(cmd, exec_path);
			g_krsh.status_code = NO_EXECUTION_PERMISSION;
			return (ERROR_DURING_EXECUTION);
		}
		free(exec_path);
		free(paths[i]);
		free(temp);
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
static int	search_for_executable(t_command *cmd, char **argv)
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

static void	ext_not_found(t_command *cmd)
{
	int i;
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
	if (!cmd->argv[0][0] || (exec_builtin(cmd) == EXIT_FAILURE
							&& search_env_path(cmd, cmd->argv) == EXIT_FAILURE
							&& search_for_executable(cmd, cmd->argv)
							== EXIT_FAILURE))
	{
		write(STDERR_FILENO, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(STDERR_FILENO, " :Command not founddddd\n", 21);
		exit_minishell(g_krsh.cmds, ERROR_COMMAND_NOT_FOUND);
	}
}

/**
 * @brief			Function to execute a simple command
 *
 * @param cmd		Command struct to execute
 * @param c			command as a char *
 * @param av		command and its parameters for use by execve
 * @return int		Status code of child process after execution
 */
int	exec_simple_cmd(t_command *cmd)
{
	pid_t	pid;

	if (exec_builtin_parent(cmd) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	pid = fork();
	if (pid == -1)
	{
		ft_printf("Error while forking\n");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (perform_io_redirections(cmd) == EXIT_FAILURE)
			exit_minishell(g_krsh.cmds, EXIT_FAILURE);
		if (cmd->argv)
			ext_not_found(cmd);
		exit_minishell(g_krsh.cmds, g_krsh.status_code);
	}
	else
		signal(SIGINT, SIG_IGN);
	g_krsh.last_child_pid = pid;
	return (EXIT_SUCCESS);
}
