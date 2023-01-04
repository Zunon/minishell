/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:00:33 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/05 01:14:12 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	t_redirect *iterator;

	iterator = cmd->redirects;
	if (piper(cmd) == -1)
		return (-1);
	while (iterator) /* Iterate through redireciton list */
	{
		if (iterator->direction == r_input)
			redirect_input(cmd, iterator);
		else if (iterator->direction == r_output || iterator->direction == r_output_append)
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
 * @brief			Allocate memory for required number of pipes & open necessary file
 * 					descriptors.
 * 					First and last pipe are dummy pipes with STDIN and STDOUT
 *
 */
void prepare_pipes()
{
	int i;

	i = 0;
	zundra.pipes = malloc(sizeof(int *) * (zundra.num_of_cmds + 1));
	while (i <= zundra.num_of_cmds)
	{
		zundra.pipes[i] = malloc(sizeof(int) * 2);
		if (i != 0 && i != zundra.num_of_cmds)
			pipe(zundra.pipes[i]);
		i++;
	}
	zundra.pipes[0][0] = STDIN_FILENO;
	zundra.pipes[0][1] = STDOUT_FILENO;
	zundra.pipes[zundra.num_of_cmds][0] = STDIN_FILENO;
	zundra.pipes[zundra.num_of_cmds][1] = STDOUT_FILENO;
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