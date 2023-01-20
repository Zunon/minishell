/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:35:44 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/20 20:17:54 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_list	*extract_words(t_token *list)
{
	t_list	*words;
	t_list	*node;
	char	*cont;

	if (!list)
		return (NULL);
	words = NULL;
	while (list && list->type != PIPE)
	{
		if (!list->prev && list->type == WORD)
		{
			cont = ft_strdup(list->contents);
			node = ft_lstnew(cont);
			ft_lstadd_back(&words, node);
		}
		if (list->type == WORD && list->prev && list->prev->type != REDIRECTION)
		{
			cont = ft_strdup(list->contents);
			node = ft_lstnew(cont);
			ft_lstadd_back(&words, node);
		}
		list = list->next;
	}
	return (words);
}
