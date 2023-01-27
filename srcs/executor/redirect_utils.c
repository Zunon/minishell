/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:00:33 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/27 15:44:29 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief			Redirect input to a specific file for a command
 *
 * @param cmd		Currently executing command
 * @param current	Current redirector in the list of redirections of the
 * 					command cmd
 * @return int		Error code of operation (0 on SUCCESS, -1 on ERROR)
 */
int	redirect_input(t_command *cmd, t_redirect *current)
{
	cmd->fd_in = open(current->redirectee, current->flags, 0644);
	if (cmd->fd_in == -1)
	{
		perror("File does not exist!");
		return (EXIT_FAILURE);
	}
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
	{
		perror("Error while duping pipe to STDIN: ");
		return (EXIT_FAILURE);
	}
	if (close(cmd->fd_in) == -1)
	{
		perror("Error while closing input file: ");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief			Redirect output to a specific file for a command
 *
 * @param cmd		Currently executing command
 * @param current	Current redirector in the list of redirections of the cmd
 * @return int		Error code of operation (0 on SUCCESS, -1 on ERROR)
 */
int	redirect_output(t_command *cmd, t_redirect *current)
{
	cmd->fd_out = open(current->redirectee, current->flags, 0644);
	if (cmd->fd_out == -1)
	{
		perror("Error while opening file: ");
		return (EXIT_FAILURE);
	}
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
	{
		perror("Error while duping pipe to STDOUT: ");
		return (EXIT_FAILURE);
	}
	if (close(cmd->fd_out) == -1)
	{
		perror("Error while closing output file: ");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	redirect_heredoc(t_redirect *current)
{
	if (dup2(g_krsh.heredocs[current->here_doc_pipe][0], STDIN_FILENO) == -1)
	{
		perror("Error while duping pipe to STDIN: ");
		return (EXIT_FAILURE);
	}
	if (close(g_krsh.heredocs[current->here_doc_pipe][0]) == -1)
	{
		perror("HEREDOC - Error while closing read pipe end: ");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief			Close all pipes safely from the child process
 *
 * @return int
 */
static int	close_child_pipes(t_command *cmd)
{
	if (cmd->pipe_in != NO_PIPE)
	{
		if (close(g_krsh.pipes[cmd->pipe_in][0]) == -1)
			return (EXIT_FAILURE);
		if (close(g_krsh.pipes[cmd->pipe_in][1]) == -1)
			return (EXIT_FAILURE);
	}
	if (cmd->pipe_out != NO_PIPE)
	{
		if (close(g_krsh.pipes[cmd->pipe_out][0]) == -1)
			return (EXIT_FAILURE);
		if (close(g_krsh.pipes[cmd->pipe_out][1]) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief			Function to pipe input and output to and from commands
 * 					following and preceding the currently executing command.
 * 					command[i] reads from pipe i and writes to pipe[i+1]. To
 * 					account for all varieties of commands, 2 artificial pipes
 * 					are created before the first command and after the last
 * 					command mimicking STDIN & STDOUT
 *
 * @param cmd		Currently executing command
 * @return int		Status code of the closing pipes and dupes done
 */
int	piper(t_command *cmd)
{
	if (g_krsh.num_of_cmds == 1)
		return (EXIT_SUCCESS);
	if (cmd->pipe_in != NO_PIPE)
	{
		if (dup2(g_krsh.pipes[cmd->pipe_in][0], STDIN_FILENO) == -1)
		{
			perror("CHILD - Error while duping pipe to STDIN: ");
			return (EXIT_FAILURE);
		}
	}
	if (cmd->pipe_out != NO_PIPE)
	{
		if (dup2(g_krsh.pipes[cmd->pipe_out][1], STDOUT_FILENO) == -1)
		{
			perror("CHILD - Error while duping pipe to STDOUT: ");
			return (EXIT_FAILURE);
		}
	}
	return (close_child_pipes(cmd));
}
