/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collapse_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 01:05:14 by kalmheir          #+#    #+#             */
/*   Updated: 2023/01/21 17:11:02 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*find_open_quote(enum e_token_type *quote_type, t_token *iterator)
{
	enum e_token_type	other_type;
	t_bool				enclosed;

	enclosed = FALSE;
	if ((*quote_type) == SINGLE_QUOTE)
		other_type = DOUBLE_QUOTE;
	else
		other_type = SINGLE_QUOTE;
	while (iterator && (iterator->type != (*quote_type) || enclosed))
	{
		if (iterator->type == other_type)
			enclosed = !enclosed;
		iterator = iterator->next;
	}
	return (iterator);
}

t_token	*catch_unclosed_quotes(t_token **list)
{
	if (*list)
		clear_tokenlist(list);
	(*list) = ft_calloc(1, sizeof(t_token));
	*(*list) = (t_token){ERROR, ft_strdup("UNCLOSED QUOTATION"), NULL, NULL};
	return (*list);
}

void	splice_quote(t_token **list, t_token *iterator, t_token *remainder,
					t_token *newtoken)
{
	if (iterator)
		iterator->next = newtoken;
	newtoken->prev = iterator;
	newtoken->next = remainder;
	if (remainder)
		remainder->prev = newtoken;
	if (!newtoken->prev) {
		fd_printf(STDERR_FILENO, "newtoken->prev is NULL");
		*list = newtoken;
	}
}

void	find_closed_quote(enum e_token_type *quote_type, t_token **iterator,
						t_token **open_quote, t_token **close_quote)
{
	(*open_quote) = (*iterator);
	(*iterator) = (*open_quote)->prev;
	if ((*iterator))
		(*iterator)->next = NULL;
	(*open_quote)->prev = NULL;
	(*close_quote) = (*open_quote)->next;
	while ((*close_quote) && (*close_quote)->type != (*quote_type))
		(*close_quote) = (*close_quote)->next;
}

/**
 * @brief Collapse the quotations in the token list into word tokens
 * @param single boolean indicating type of quotation to collapse
 * @param list linked list of tokens we are operating on
 * @return linked list of tokens after the collapse of the desired quotations
 */
t_token	*collapse_quotes(enum e_token_type quote_type, t_token *list)
{
	t_token	*tokens[5];

	tokens[0] = list;
	while (tokens[0])
	{
		tokens[0] = find_open_quote(&quote_type, tokens[0]);
		if (!tokens[0])
			return (list);
		find_closed_quote(&quote_type, &tokens[0], &tokens[1], &tokens[2]);
		if (!tokens[2])
			return (catch_unclosed_quotes(&list));
		tokens[3] = tokens[2]->next;
		tokens[2]->next = NULL;
		if (tokens[3])
			tokens[3]->prev = NULL;
		tokens[4] = merge_quotation_tokens(tokens[1]);
		if (!tokens[0])
			list = tokens[4];
		clear_tokenlist(&tokens[1]);
		splice_quote(&list, tokens[0], tokens[3], tokens[4]);
		tokens[0] = tokens[3];
	}
	return (list);
}
