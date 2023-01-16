/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:30:54 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/14 23:56:05 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "minishell.h"

enum e_direction	get_direction(char *direction)
{
	if (ft_strncmp(">>", direction, 3) == 0)
		return (OUTPUT_APPEND);
	if (ft_strncmp("<<", direction, 3) == 0)
		return (HERE_DOC);
	if (ft_strncmp(">", direction, 2) == 0)
		return (OUTPUT);
	return (INPUT);
}

/**
 * @todo handle the HERE_DOC case
 */
int	get_file_open_flags(enum e_direction direction)
{
	if (direction == INPUT)
		return (O_CREAT | O_RDONLY);
	if (direction == OUTPUT)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	return (O_CREAT | O_WRONLY | O_APPEND);
}

t_redirect	*extract_redirects(t_token *list)
{
	t_redirect	*redirs;
	t_redirect	*iterator;
	t_redirect	*temp;

	if (!list)
		return (NULL);
	redirs = malloc(sizeof(t_redirect));
	iterator = redirs;
	while (list && list->type != PIPE)
		push_redirection(&list, &iterator);
	if (iterator == redirs)
	{
		free(redirs);
		redirs = NULL;
		return (redirs);
	}
	temp = redirs;
	while (temp->next != iterator)
		temp = temp->next;
	free(iterator);
	temp->next = NULL;
	return (redirs);
}

t_list	*extract_words(t_token *list)
{
	t_list	*words;
	t_list	*iterator;

	if (!list)
		return (NULL);
	iterator = words;
	words = NULL;
	while (list && list->type != PIPE)
	{
		if (!list->prev && list->type == WORD)
			ft_lstadd_back(&words, ft_lstnew(ft_strdup(list->contents)));
		if (list->type == WORD && list->prev && list->prev->type != REDIRECTION)
			ft_lstadd_back(&words, ft_lstnew(ft_strdup(list->contents)));
		list = list->next;
	}
	return (words);
}

t_command	*token_to_cmd_converter(t_token *list)
{
	t_token		*iterator;
	t_command	*cmd;
	t_command	*pipeline;
	int			i;

	if (!list)
		return (NULL);
	i = 0;
	iterator = list;
	cmd = malloc(sizeof(t_command));
	pipeline = cmd;
	while (iterator)
		construct_command(i, &iterator, &cmd);
	if (cmd == pipeline)
	{
		free(pipeline);
		pipeline = NULL;
		return (pipeline);
	}
	free_cmdnode(cmd, pipeline);
	return (pipeline);
}
