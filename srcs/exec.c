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
 * @brief 			Find and execute commands based on current directory (Eg. run executables)
 *
 * @param cmd		The command to be executed
 * @param argv		The parameters to the command
 * @param envp		Environment variables
 * @return int		Status code of execution (1 on SUCCESS, 0 on 'CMD NOT FOUND')
 */
int search_relative_path(char *cmd, char **argv)
{
	if (ft_strchr(cmd, '/') != 0 && execve(cmd, argv, zundra.envp) == -1)
		ft_printf("Error during execution of program!");
	return 0;
}

/**
 * @brief			Redirect input to a specific file for a command
 *
 * @param cmd		Currently executing command
 * @param current	Current redirector in the list of redirections of the command cmd
 * @return int		Error code of operation (0 on SUCCESS, -1 on ERROR)
 */
int redirect_input(t_command *cmd, t_redirect *current)
{
	cmd->fd_in = open(current->redirectee.word, current->flags, 0777);
	if (cmd->fd_in == -1)
	{
		perror("File does not exist!");
		return (-1);
	}
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
	{
		perror("Error while duping pipe to STDIN: ");
		return (-1);
	}
	if (close(cmd->fd_in) == -1)
	{
		perror("Error while closing file: ");
		return (-1);
	}
	return (0);
}

/**
 * @brief			Redirect output to a specific file for a command
 *
 * @param cmd		Currently executing command
 * @param current	Current redirector in the list of redirections of the command cmd
 * @return int		Error code of operation (0 on SUCCESS, -1 on ERROR)
 */
int redirect_output(t_command *cmd, t_redirect *current)
{
	cmd->fd_out = open(current->redirectee.word, current->flags, 0777);
	if (cmd->fd_out == -1)
	{
		perror("File does not exist!");
		return -1;
	}
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
	{
		perror("Error while duping pipe to STDOUT: ");
		return (-1);
	}
	if (close(cmd->fd_out) == -1)
	{
		perror("Error while closing file: ");
		return (-1);
	}
	return (0);
}

/**
 * @brief			Function to open necessary files and perform all redirections from left->right.
 * 					If there are pipes, then the necessary piping is handled as well.
 * 					Handles input, output, output append, and heredoc
 *
 * @param cmd		Currently executing command
 * @return int		Status code (discard if not needed)
 */
int perform_IO_redirections(t_command *cmd)
{
	int fd;
	t_redirect *iterator;

	iterator = cmd->redirects;
	if (piper(cmd) == -1)
		return (-1);
	while (iterator) /* Iterate through redireciton list */
	{
		if (iterator->direction == r_input)
			redirect_input(cmd, iterator);
		else if (iterator->direction == r_output || iterator->direction  == r_output_append)
			redirect_output(cmd, iterator);
		else
		{
			// heredoc
		}
		iterator = iterator->next;
	}
	return (0);
}

/**
 * @brief			Function to pipe input and output to and from commands following and
 *					preceding the currently executing command. command[i] reads from pipe i and writes
					to pipe[i+1]. To account for all varieties of commands, 2 artificial pipes are
					created before the first command and after the last command mimicking STDIN & STDOUT
 *
 * @param cmd		Currently executing command
 * @return int		Status code of the closing pipes and dupes done
 */
int piper(t_command *cmd)
{
	int i;
	int error_code;

	i = 1;
	if (dup2(zundra.pipes[cmd->id][0], STDIN_FILENO) == -1)
	{
		perror("Error while duping pipe to STDIN: ");
		return (-1);
	}
	if (dup2(zundra.pipes[cmd->id + 1][1], STDOUT_FILENO) == -1)
	{
		perror("Error while duping pipe to STDOUT: ");
		return (-1);
	}
	while (i < zundra.num_of_cmds)
	{
		if (close(zundra.pipes[i][0]) == -1)
		{
			perror("Error while closing pipe: ");
			return (-1);
		}
		if (close(zundra.pipes[i][1]) == -1)
		{
			perror("Error while closing pipe: ");
			return (-1);
		}
		i++;
	}
	return (1);
}

/**
 * @brief			Function to execute a simple command
 *
 * @param cmd		Command struct to execute
 * @param c			command as a char *
 * @param av		command and its parameters for use by execve
 * @return int		Status code of child process after execution
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
		if (perform_IO_redirections(cmd) == -1)
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