/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:04:06 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/05 15:32:36 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief			Function to deallocate memory for the linked list of redirections
 * 					belongin to any command
 *
 * @param redir		Linked list of redirections for the command
 */
static void free_redirects(t_redirect *redir)
{
	t_redirect *temp;

	if (!redir)
		return;
	while (redir)
	{
		temp = redir;
		redir = redir->next;
		if (temp->direction == r_here_doc)
		{
			if (unlink(temp->redirectee) == -1)
				perror("Error while deleting heredoc temp file: ");
			free(temp->here_doc_delim);
		}
		free(temp->redirectee);
		free(temp);
	}
}

/**
 * @brief			Function to deallocate memory for a linked list of commands in a pipeline
 *
 * @param cmd		Linked list of commands
 */
void free_commands(t_command *cmd)
{
	t_command *temp;
	int i;

	i = 0;
	if (!cmd)
		return;
	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		free_redirects(temp->redirects);
		ft_lstclear(&cmd->words, free);
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		if (cmd->argv)
			free(cmd->argv);
		if (temp)
			free(temp);
	}
}
