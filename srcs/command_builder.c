/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:30:54 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/14 23:22:41 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


enum e_direction get_direction(char *direction)
{
	if (ft_strncmp(">>", direction, 3) == 0)
		return (OUTPUT_APPEND);
	if (ft_strncmp("<<", direction, 3) == 0)
		return (HERE_DOC);
	if (ft_strncmp(">", direction, 2) == 0)
		return (OUTPUT);
	return (INPUT);
}

t_redirect *extract_redirects(t_token *list)
{
	t_redirect *redirs;
	t_redirect *iterator;
	t_redirect *temp;

	if (!list)
		return (NULL);
	redirs = malloc(sizeof(t_redirect));
	iterator = redirs;
	while (list && list->type != PIPE)
	{
		if (list->type == REDIRECTION)
		{
			iterator->redirectee = list->next->contents;
			iterator->direction = get_direction(list->contents);
			iterator->next = malloc(sizeof(t_redirect));
			iterator = iterator->next;
			list = list->next;
		}
		list = list->next;
	}
	if (iterator == redirs)
	{
		free(redirs);
		redirs = NULL;
		return redirs;
	}
	temp = redirs;
	while (temp->next != iterator)
		temp = temp->next;
	free(iterator);
	temp->next = NULL;
	return (redirs);
}

t_list *extract_words(t_token *list)
{
	t_list *words;
	t_list *iterator;

	if (!list)
		return (NULL);
	iterator = words;
	words = NULL;
	while(list && list->type != PIPE)
	{
		if (!list->prev && list->type == WORD)
			ft_lstadd_back(&words, ft_lstnew(ft_strdup(list->contents)));
		if (list->type == WORD && list->prev && list->prev->type != REDIRECTION)
			ft_lstadd_back(&words, ft_lstnew(ft_strdup(list->contents)));
		list = list->next;
	}
	return (words);
}

t_token *get_next_cmd(t_token *list)
{
	while (list && list->type != PIPE)
		list = list->next;
	if (list && list->type == PIPE)
		list = list->next;
	return (list);
}


// more thtan 2 < or >, ||
// variable expansions - first char after dollar sign should be underscore or alpha
// each quote should be each its own individial token
// doolar sign next chraif not valid - then WORD U $
// dollar sign then double quotes then name -
// dollar sign then single quotes then name -

t_command *token_to_cmd_converter(t_token *list)
{
	t_token *iterator;
	t_command *cmd;
	t_command *pipeline;
	t_command *temp;
	int i;

	if (!list)
		return (NULL);
	i = 0;
	iterator = list;
	cmd = malloc(sizeof(t_command));
	pipeline = cmd;
	while (iterator)
	{
		cmd->id = i;
		cmd->redirects = extract_redirects(iterator);
		cmd->words = extract_words(iterator);
		iterator = get_next_cmd(iterator);
		cmd->next = malloc(sizeof(t_command));
		cmd = cmd->next;
		i++;
	}
	if (cmd == pipeline)
	{
		free(pipeline);
		pipeline = NULL;
		return (pipeline);
	}
	temp = pipeline;
	while (temp && temp->next != cmd)
		temp = temp->next;
	free(cmd);
	temp->next = NULL;
	return (pipeline);
}