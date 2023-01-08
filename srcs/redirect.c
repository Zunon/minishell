/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:00:33 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/05 16:05:15 by rriyas           ###   ########.fr       */
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
static int redirect_input(t_command *cmd, t_redirect *current)
{
	cmd->fd_in = open(current->redirectee.word, current->flags, 0777);
	if (cmd->fd_in == -1)
	{
		perror("CHILD - File does not exist!");
		return (EXIT_FAILURE);
	}
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
	{
		perror("CHILD - Error while duping pipe to STDIN: ");
		return (EXIT_FAILURE);
	}
	if (close(cmd->fd_in) == -1)
	{
		perror("CHILD - Error while closing input file: ");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief			Redirect output to a specific file for a command
 *
 * @param cmd		Currently executing command
 * @param current	Current redirector in the list of redirections of the command cmd
 * @return int		Error code of operation (0 on SUCCESS, -1 on ERROR)
 */
static int redirect_output(t_command *cmd, t_redirect *current)
{
	cmd->fd_out = open(current->redirectee.word, current->flags, 0777);
	if (cmd->fd_out == -1)
	{
		perror("CHILD - File does not exist!");
		return (EXIT_FAILURE);
	}
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
	{
		perror("CHILD - Error while duping pipe to STDOUT: ");
		return (EXIT_FAILURE);
	}
	if (close(cmd->fd_out) == -1)
	{
		perror("CHILD - Error while closing output file: ");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief			Close all pipes safely from the child process
 * 
 * @return int 
 */
static int close_child_pipes()
{
	int i;

	i = 1;
	while (i < zundra.num_of_cmds)
	{
		if (close(zundra.pipes[i][0]) == -1)
		{
			perror("CHILD - Error while closing pipe read end: ");
			return (EXIT_FAILURE);
		}
		if (close(zundra.pipes[i][1]) == -1)
		{
			perror("CHILD - Error while closing pipe write end: ");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
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
static int piper(t_command *cmd)
{
	if (dup2(zundra.pipes[cmd->id][0], STDIN_FILENO) == -1)
	{
		perror("CHILD - Error while duping pipe to STDIN: ");
		return (EXIT_FAILURE);
	}
	if (dup2(zundra.pipes[cmd->id + 1][1], STDOUT_FILENO) == -1)
	{
		perror("CHILD - Error while duping pipe to STDOUT: ");
		return (EXIT_FAILURE);
	}
	return (close_child_pipes());
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
	int status;

	status  = EXIT_SUCCESS;
	iterator = cmd->redirects;
	if (piper(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (iterator && status != EXIT_FAILURE) /* Iterate through redirection list */
	{
		if (iterator->direction == r_input)
			status = redirect_input(cmd, iterator);
		else if (iterator->direction == r_output || iterator->direction == r_output_append)
			status = redirect_output(cmd, iterator);
		else
		{
			// heredoc
		}
		iterator = iterator->next;
	}
	return (status);
}