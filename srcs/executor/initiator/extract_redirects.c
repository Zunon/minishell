/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:33:02 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/20 20:55:23 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static enum e_direction	get_direction(char *direction)
{
	if (ft_strncmp(">>", direction, 3) == 0)
		return (OUTPUT_APPEND);
	if (ft_strncmp("<<", direction, 3) == 0)
		return (HERE_DOC);
	if (ft_strncmp(">", direction, 2) == 0)
		return (OUTPUT);
	return (INPUT);
}

static int	get_file_open_flags(enum e_direction direction)
{
	if (direction == HERE_DOC)
		return (O_CREAT | O_WRONLY);
	if (direction == INPUT)
		return (O_RDONLY);
	if (direction == OUTPUT)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	return (O_CREAT | O_WRONLY | O_APPEND);
}

static void	push_redirection(t_token **list, t_redirect **iterator)
{
	if ((*list)->type == REDIRECTION)
	{
		(*iterator)->direction = get_direction((*list)->contents);
		if ((*iterator)->direction == HERE_DOC)
			(*iterator)->here_doc_delim = ft_strdup((*list)->next->contents);
		else
		{
			(*iterator)->redirectee = ft_strdup((*list)->next->contents);
			(*iterator)->flags = get_file_open_flags((*iterator)->direction);
		}
		(*iterator)->next = malloc(sizeof(t_redirect));
		(*iterator) = (*iterator)->next;
		(*list) = (*list)->next;
	}
	(*list) = (*list)->next;
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
