/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:35:27 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/12 19:06:00 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief			Find and execute commands from the PATH environment variable
 *
 * @param cmd		The command to be executed
 * @param argv		The parameters to the command
 * @param envp		Environment variables
 * @return int		Status code of execution (1 on SUCCESS, 0 on 'CMD NOT FOUND')
 */
static int search_absolute_path(char **argv)
{
	int i;
	char *exec_path;
	char **paths;
	t_pair *path;

	path = retrieve_from_dict(zundra.env_mngr, "PATH");
	if (!path || !path->value)
		return (EXIT_FAILURE);
	paths = ft_split(path->value, ':');
	i = 0;
	while (paths[i])
	{
		exec_path = ft_strjoin(ft_strjoin(paths[i], "/"), argv[0]);
		if (access(exec_path, F_OK) != -1 && execve(exec_path, argv, zundra.envp) == -1)
		{
			if (access(exec_path, X_OK) == -1)
			{
				perror("Error during execution of program: ");
				if (zundra.num_of_cmds > 1)
					exit(NO_EXECUTION_PERMISSION);
			}
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
 * @brief 			Find and execute commands based on current directory (Eg. run executables)
 *
 * @param cmd		The command to be executed
 * @param argv		The parameters to the command
 * @param envp		Environment variables
 * @return int		Status code of execution (1 on SUCCESS, 0 on 'CMD NOT FOUND')
 */
static int search_relative_path(char **argv)
{
	if (ft_strchr(argv[0], '/') != 0 && execve(argv[0], argv, zundra.envp) == -1)
	{
		if (access(argv[0], X_OK) == -1)
		{
			perror("Error during execution: ");
			if (zundra.num_of_cmds > 1)
				exit(NO_EXECUTION_PERMISSION);
			zundra.status_code = NO_EXECUTION_PERMISSION;
			return (ERROR_COMMAND_NOT_FOUND);
		}
		perror("Error during execution: ");
		return (ERROR_DURING_EXECUTION);
	}
	return (EXIT_FAILURE);
}

/**
 * @brief			Function to execute a simple command
 *
 * @param cmd		Command struct to execute
 * @param c			command as a char *
 * @param av		command and its parameters for use by execve
 * @return int		Status code of child process after execution
 */
int exec_simple_cmd(t_command *cmd)
{
	pid_t pid;

	if (!cmd->next && exec_builtin(cmd) == EXIT_SUCCESS)
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
		if (perform_IO_redirections(cmd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (exec_builtin(cmd) == EXIT_FAILURE &&
				search_absolute_path(cmd->argv) == EXIT_FAILURE &&
				search_relative_path(cmd->argv) == EXIT_FAILURE)
		{
			write(STDERR_FILENO, "Command not found\n", 19);
			exit(ERROR_COMMAND_NOT_FOUND);
		}
	}
	else
		signal(SIGINT, SIG_IGN);
	zundra.last_child_pid = pid;
	return (EXIT_SUCCESS);
}
