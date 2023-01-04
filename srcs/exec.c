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
int search_absolute_path(char *cmd, char **argv)
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
				if (execve(exec_path, argv, zundra.envp) == -1)
					perror("Error during execution of program!");
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
int search_relative_path(char *cmd, char **argv)
{
	if (ft_strchr(cmd, '/') != 0 && execve(cmd, argv, zundra.envp) == -1)
		ft_printf("Error during execution of program!");
	return 0;
}

/**
 * @brief		Function to open necessary files and perform all redirections from left->right.
 * 				Handles inout, output, output append, and heredoc
 *
 * @param cmd	Currently executing command
 * @return int	Status code (discard if not needed)
 */
int perform_redirections(t_command *cmd)
{
	int fd;
	t_redirect *iterator;

	iterator = cmd->redirects;
	dup2(zundra.pipes[cmd->id][0], STDIN_FILENO);
	dup2(zundra.pipes[cmd->id + 1][1], STDOUT_FILENO);
	for (int i = 0; i< 4 ;i++)
	{
		if (i != 0 && i != 3 ) /*  Ignore first and last pipe */
		{
			close (zundra.pipes[i][0]);
			close(zundra.pipes[i][1]);
		}
	}
	while (iterator) /* Iterate through redireciton list */
	{
		if (iterator->direction == r_input)
		{
			cmd->fd_in = open(iterator->redirectee.word, iterator->flags, 0777);
			if (cmd->fd_in == -1)
			{
				perror("File does not exist!");
				return -1;
			}
			dup2(cmd->fd_in, STDIN_FILENO);
			close(cmd->fd_in);
		}
		else if (iterator->direction == r_output || r_output_append)
		{
			cmd->fd_out = open(iterator->redirectee.word, iterator->flags, 0777);
			if (cmd->fd_out == -1)
			{
				perror("File does not exist!");
				return -1;
			}
			dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
		else
		{
			// heredoc
		}
		iterator = iterator->next;
	}

	return 0;
}

/**
 * @brief		Function to undo redirections back to stdout OR pipe for use by next command
 *
 * @param cmd	Currently executing command
 * @return int	Status code (discard if not needed)
 */
int undo_redirections(t_command *cmd)
{
	dup2(cmd->stdout_old, STDOUT_FILENO);
	close(cmd->stdout_old);
	dup2(cmd->stdin_old, STDIN_FILENO);
	close(cmd->stdin_old);
	return 0;
}

/**
 * @brief		Function to execute a simple command
 *
 * @param cmd	Command struct to execute
 * @param c		command as a char *
 * @param av	command and its parameters for use by execve
 * @return int	Status code of child process after execution
 */
int cmd_executor(t_command *cmd, char *c, char **av)
{
	pid_t pid;
	int child_status;

	pid = fork();
	if (pid == -1)
	{
		ft_printf("Error while forking\n");
		return -1;
	}
	if (pid == 0)
	{
		if (perform_redirections(cmd) == -1)
			return -1;
		if (search_absolute_path(c, av) == 0)
		{
			if (!search_relative_path(c, av))
			{
				ft_printf("minishell: command not found\n");
				return 0;
			}
		}
	}
	zundra.status_code = WEXITSTATUS(child_status);
	return WEXITSTATUS(child_status);
}
