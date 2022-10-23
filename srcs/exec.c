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
 * @brief Find and execute commands from the PATH environment variable
 *
 * @param cmd	The command to be executed
 * @param argv	The parameters to the command
 * @param envp	Environment variables
 * @return int	Status code of execution (1 on SUCCESS, 0 on 'CMD NOT FOUND')
 */
int search_absolute_path(char *cmd, char **argv, char **envp)
{
	int i;
	DIR *d;
	struct dirent *dir;
	char *exec_path;
	char *path = getenv("PATH");
	char **paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		d = opendir(paths[i]);
		dir = readdir(d);
		while (dir)
		{
			if (ft_strncmp(dir->d_name, cmd, 255) == 0)
			{
				exec_path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
				if (execve(exec_path, argv, envp) == -1)
					perror("Error during execution of program!");
				return 1;
			}
			dir = readdir(d);
		}
		closedir(d);
		i++;
	}
	return 0;
}

/**
 * @brief Find and execute commands based on current directory (Eg. run executables)
 *
 * @param cmd	The command to be executed
 * @param argv	The parameters to the command
 * @param envp	Environment variables
 * @return int	Status code of execution (1 on SUCCESS, 0 on 'CMD NOT FOUND')
 */
int search_relative_path(char *cmd, char **argv, char **envp)
{
	if (ft_strchr(cmd, '/') != 0 && execve(cmd, argv, envp) == -1)
		ft_printf("Error during execution of program!");
	return 0;
}

/**
 * @brief Execute a terminal command in a child process
 *
 * @param cmd	The command to be executed
 * @param argv	The parameters to the command
 * @param envp	Environment variables
 * @return int Status code of child process
 */
int execute_cmd(char *cmd, char **argv, char **envp)
{
	pid_t pid;
	int child_status;

	pid = fork();
	waitpid(-1, &child_status, 0);
	if (pid == -1)
	{
		ft_printf("Error while forking\n");
		return -1;
	}
	if (pid == 0)
	{
		if (!search_absolute_path(cmd, argv, envp))
		{
			if (!search_relative_path(cmd, argv, envp))
			{
				ft_printf("minishell: command not found\n");
				return 0;
			}
		}
	}
	return child_status;
}
