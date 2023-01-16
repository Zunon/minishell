/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_adjacent_words.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:19:09 by kalmheir          #+#    #+#             */
/*   Updated: 2023/01/17 01:05:31 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clean_endpoints(t_token *new_item, t_token **list, t_token **iterator)
{
	if ((*iterator)->prev)
	{
		(*iterator)->prev->next = new_item;
		new_item->prev = (*iterator)->prev;
	}
	else
	{
		(*list) = new_item;
		new_item->prev = NULL;
	}
	if ((*iterator)->next->next)
	{
		(*iterator)->next->next->prev = new_item;
		new_item->next = (*iterator)->next->next;
	}
	else
		new_item->next = NULL;
}

void	merge_found(t_token *new_item, enum e_token_type *merge_type,
					t_token **list, t_token **iterator)
{
	if ((*iterator)->type == QUOTED || (*iterator)->next->type == QUOTED)
		(*merge_type) = QUOTED;
	else
		(*merge_type) = WORD;
	new_item = malloc(sizeof(t_token));
	new_item->type = (*merge_type);
	new_item->contents = ft_strjoin((*iterator)->contents,
			(*iterator)->next->contents);
	clean_endpoints(new_item, list, iterator);
	(*iterator)->next->next = NULL;
	clear_tokenlist(iterator);
	(*iterator) = new_item;
}

/**
 * @brief Merges adjacent words in the list
 * @param list linked list of tokens to be scanned and merged
 * @return list with merged adjacent words
 */
t_token	*merge_words(t_token *list)
{
	t_token				*iterator;
	t_token				*new_item;
	enum e_token_type	merge_type;

	iterator = list;
	while (iterator)
	{
		if (iterator->next && (iterator->type == WORD || iterator->type
				== QUOTED) && (iterator->next->type == WORD
				|| iterator->next->type == QUOTED))
		{
			merge_found(new_item, &merge_type, &list, &iterator);
		}
		else
			iterator = iterator->next;
	}
	return (list);
}
