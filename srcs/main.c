/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:54:26 by rriyas            #+#    #+#             */
/*   Updated: 2022/09/03 19:01:35 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list *freeable = NULL;

/**
 * @brief Function to handle various signals in the program
 *
 * @param sig - signal recieved by the program
 */
void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_lstclear(&freeable, free);
		exit(0);
	}
}

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
			if (ft_strlen(cmd) == ft_strlen(dir->d_name) && ft_strncmp(dir->d_name, cmd, ft_strlen(dir->d_name)) == 0)
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
	DIR *d;
	struct dirent *dir;
	char *curr_dir;
	char *path;
	curr_dir = getcwd(NULL, 1);
	// d = opendir(curr_dir);
	// dir = readdir(d);
	// while (dir)
	// {
	// 	if (ft_strncmp(dir->d_name, cmd, ft_strlen(dir->d_name)) == 0)
	// 	{
	// 		if (execve(ft_strjoin(curr_dir, cmd), argv, envp) == -1)
	// 			perror("Error during execution of program!");
	// 		return 1;
	// 	}
	// 	dir = readdir(d);
	// }
	// closedir(d);
	path = ft_strjoin(ft_strjoin(curr_dir, "/"), cmd);
	if (execve(path, argv, envp) == -1)
		perror("Error during execution of program!");
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
	wait(&child_status);
	if (pid == -1)
	{
		perror("Error while forking\n");
		return -1;
	}
	if (pid == 0)
	{
		if (!search_absolute_path(cmd, argv, envp))
		{
			if (!search_relative_path(cmd, argv, envp))
			{
				perror("minishell: command not found: ");
				perror(cmd);
				return 0;
			}
		}
	}
	return child_status;
}

int main(int argc, char **argv, char **envp)
{
	char *s;

	(void)argc;
	(void)argv;
	(void)envp;
	signal(SIGINT, &sig_handler);
	while (2)
	{
		s = readline("minishell ^-^ : ");
		ft_lstadd_back(&freeable, ft_lstnew(s));
		add_history(s);
		argv = ft_split(s, ' ');
		execute_cmd(argv[0], argv, envp);
	}
	return (0);
}