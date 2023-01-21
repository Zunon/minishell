/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:28:13 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/21 17:12:19 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief			Handle environment variable expansion (if any)
 *
 * @param word		Variable that needs to be expanded
 * @return char*	Expanded variable
 */
char	*expand(char *word)
{
	t_pair	*pair;
	char	*result;

	if (!word || !*word)
		return (NULL);
	if (*word == '?')
	{
		return (ft_itoa(g_krsh.status_code));
	}
	pair = retrieve_from_dict(g_krsh.env_mngr, word);
	if (pair)
		result = ft_strdup(pair->value);
	else
		result = ft_strdup("");
	return (result);
}

t_command	*parse_input(const char *input)
{
	t_token	*list;

	list = tokenize((char *)input);
	if (list && list->type == ERROR)
	{
		write(STDERR_FILENO, "Token Error!\n", 13);
		clear_tokenlist(&list);
		return (NULL);
	}
	else if (!parse_pipeline(list))
	{
		write(STDERR_FILENO, "Parse Error!\n", 14);
		clear_tokenlist(&list);
		return (NULL);
	}
	return (conv_tok_to_cmd(list));
}

/**
 * @brief Free the token list given to it fully
 * @param list linked list of tokens
 */
void	clear_tokenlist(t_token **list)
{
	t_token	*holder;

	if (!list || !*list)
		return ;
	while (*list)
	{
		holder = (*list)->next;
		free((*list)->contents);
		free(*list);
		*list = holder;
	}
	list = NULL;
}

void	del_token(t_token **list, t_token **iterator)
{
	t_token	*temp;

	if ((*iterator)->prev && (*iterator)->next)
	{
		(*iterator)->prev->next = (*iterator)->next;
		(*iterator)->next->prev = (*iterator)->prev;
	}
	else if ((*iterator)->prev)
		(*iterator)->prev->next = NULL;
	else if ((*iterator)->next)
		(*list) = (*iterator)->next;
	else
		(*list) = NULL;
	temp = (*iterator)->next;
	free((*iterator)->contents);
	free((*iterator));
	(*iterator) = temp;
}

void	splice_tokens(t_token **list, t_token **iterator)
{
	t_token	*spliced_head;
	t_token	*spliced_tail;

	spliced_head = token_split((*iterator)->contents);
	spliced_tail = token_last(spliced_head);
	if ((*iterator)->prev)
	{
		spliced_head->prev = (*iterator)->prev;
		(*iterator)->prev->next = spliced_head;
	}
	else
		(*list) = spliced_head;
	if ((*iterator)->next)
	{
		spliced_tail->next = (*iterator)->next;
		(*iterator)->next->prev = spliced_tail;
	}
	else
		spliced_tail->next = NULL;
	(*iterator)->next = NULL;
	clear_tokenlist(iterator);
	(*iterator) = spliced_tail->next;
}
