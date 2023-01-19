/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:11:11 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/15 19:08:39 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief			Configure the input and output pipes for every command in
 * 					the pipeline
 *
 * 					First and last pipe are dummy pipes with STDIN and STDOUT
 *
 */
static int	configure_pipes(t_command *cmd)
{
	while(cmd)
	{
		cmd->pipe_in = cmd->id % 2;
		cmd->pipe_out = !(cmd->pipe_in);
		if (cmd->id == 0)
			cmd->pipe_in = NO_PIPE;
		if (!cmd->next)
			cmd->pipe_out = NO_PIPE;
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief			Close all pipes safely from the parent process
 *
 */
static int	close_used_pipes(int pipe_in)
{
	if (pipe_in != NO_PIPE)
	{
		if (close(g_krsh.pipes[pipe_in][0]) == -1)
		{
			perror("PARENT - Error while closing pipe read end: ");
			return (EXIT_FAILURE);
		}
		if (close(g_krsh.pipes[pipe_in][1]) == -1)
		{
			perror("PARENT - Error while closing pipe write end: ");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief			Get the number of words in the given word list.
 * 					Used to help deicde how many bytes of memory to allocate for
 * 					the argument list of a command
 *
 * @param word_lst 	t_word_lst variable to get the size of
 * @return int		Number of strings present (Excluding NULL element)
 */
static int	get_list_length(t_list *word_lst)
{
	int	i;

	i = 0;
	while (word_lst)
	{
		word_lst = word_lst->next;
		i++;
	}
	return (i);
}

/**
 * @brief			Prepare the arguments of the current command as a char**
 * 					for easy execution by execve
 *
 * @param word_lst	linked list of words
 * @return char**	argv for the currently executing command
 */
static char	**prepare_cmd_args(t_list *word_lst)
{
	char	**ret;
	int		i;

	if (!word_lst)
		return (NULL);
	i = 0;
	ret = malloc(sizeof(char *) * (1 + get_list_length(word_lst)));
	while (word_lst)
	{
		ret[i] = (char *)(word_lst->content);
		word_lst = word_lst->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

/**
 * @brief			Phase 3 of the shell - execution of commands takes place here
 *
 * @param cmd		Linked list of commands to execute in the current pipeline
 * @return int		Status code of last executed command
 */
int	executor(t_command *first_cmd)
{
	t_command	*curr;
	int			status;

	curr = first_cmd;
	if (!first_cmd)
		return (EXIT_SUCCESS);
	configure_pipes(first_cmd);
	handle_heredoc(curr);
	while (curr)
	{
		g_krsh.cmds = curr;
		curr->argv = prepare_cmd_args(curr->words);
		if (curr->pipe_out != NO_PIPE)
			pipe(g_krsh.pipes[curr->pipe_out]);
		if (curr->argv)
			exec_simple_cmd(curr);
		close_used_pipes(curr->pipe_in);
		curr = curr->next;
	}
	waitpid(g_krsh.last_child_pid, &status, 0);
	g_krsh.status_code = WEXITSTATUS(status);
	while (waitpid(-1, &status, 0) > -1)
		;
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
	return (g_krsh.status_code);
}
