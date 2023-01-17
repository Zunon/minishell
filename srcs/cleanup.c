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
static void	free_redirects(t_redirect *redir)
{
	t_redirect	*temp;

	if (!redir)
		return ;
	while (redir)
	{
		temp = redir;
		redir = redir->next;
		if (temp->direction == HERE_DOC)
			free(temp->here_doc_delim);
		free(temp->redirectee);
		free(temp);
	}
}

/**
 * @brief			Function to deallocate memory for a linked list of commands
 * 					in a pipeline
 *
 * @param cmd		Linked list of commands
 */
void	free_commands(t_command *cmd)
{
	t_command	*temp;
	int			i;

	i = 0;
	if (!cmd)
		return ;
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

void	push_redirection(t_token **list, t_redirect **iterator)
{
	if ((*list)->type == REDIRECTION)
	{
		(*iterator)->direction = get_direction((*list)->contents);
		if ((*iterator)->direction == HERE_DOC)
			(*iterator)->here_doc_delim = (*list)->next->contents;
		else
		{
			(*iterator)->redirectee = (*list)->next->contents;
			(*iterator)->flags = get_file_open_flags((*iterator)->direction);
		}
		(*iterator)->next = malloc(sizeof(t_redirect));
		(*iterator) = (*iterator)->next;
		(*list) = (*list)->next;
	}
	(*list) = (*list)->next;
}

t_token	*get_next_cmd(t_token *list)
{
	while (list && list->type != PIPE)
		list = list->next;
	if (list && list->type == PIPE)
		list = list->next;
	return (list);
}

void	free_cmdnode(t_command *cmd, t_command *pipeline)
{
	t_command	*temp;

	temp = pipeline;
	while (temp && temp->next != cmd)
		temp = temp->next;
	free(cmd);
	temp->next = NULL;
}
