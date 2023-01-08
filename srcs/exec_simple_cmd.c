/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:35:27 by rriyas            #+#    #+#             */
/*   Updated: 2022/10/22 20:36:59 by rriyas           ###   ########.fr       */
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
		if (access(exec_path, X_OK) != -1 && execve(exec_path, argv, zundra.envp) == -1)
		{
			perror("Error during execution of program!");
			return (EXIT_FAILURE);
		}
		free(exec_path);
		free(paths[i]);
		i++;
	}
	free(paths);
	return (EXIT_SUCCESS);
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
		perror("Error during execution of program!");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief			Function to execute a simple command
 *
 * @param cmd		Command struct to execute
 * @param c			command as a char *
 * @param av		command and its parameters for use by execve
 * @return int		Status code of child process after execution
 */
int exec_simple_cmd(t_command *cmd, char **argv)
{
	pid_t pid;

	if (!cmd->next && exec_builtin(cmd, argv) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	pid = fork();
	if (pid == -1)
	{
		ft_printf("Error while forking\n");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (perform_IO_redirections(cmd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (exec_builtin(cmd, argv) == EXIT_FAILURE && !search_absolute_path(argv) && !search_relative_path(argv))
		{
			write(zundra.stdout_old, "minishell: command not found\n", 30);
			zundra.status_code = 127;
			close(zundra.stdout_old);
			exit(127);
		}
	}
	zundra.last_child_pid = pid;
	return (EXIT_SUCCESS);
}
