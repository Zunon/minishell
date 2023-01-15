//
// Created by Khalifa Almheiri on 1/15/23.
//

#include "../inc/minishell.h"

/**
 * @brief Merges adjacent words in the list
 * @param list linked list of tokens to be scanned and merged
 * @return list with merged adjacent words
 */
t_token *merge_words(t_token *list)
{
	t_token *iterator;
	t_token *new_item;
	enum e_token_type merge_type;

	iterator = list;
	while (iterator)
	{
		if (iterator->next && (iterator->type == WORD || iterator->type == QUOTED) && (iterator->next->type == WORD || iterator->next->type == QUOTED))
		{
			if (iterator->type == QUOTED || iterator->next->type == QUOTED)
				merge_type = QUOTED;
			else
				merge_type = WORD;
			new_item = malloc(sizeof(t_token));
			new_item->type = merge_type;
			new_item->contents = ft_strjoin(iterator->contents, iterator->next->contents);
			if (iterator->prev) {
				iterator->prev->next = new_item;
				new_item->prev = iterator->prev;
			} else {
				list = new_item;
				new_item->prev = NULL;
			}
			if (iterator->next->next) {
				iterator->next->next->prev = new_item;
				new_item->next = iterator->next->next;
			}
			else
				new_item->next = NULL;
			iterator->next->next = NULL;
			clear_tokenlist(&iterator);
			iterator = new_item;
		}
		else
			iterator = iterator->next;
	}
	return (list);
}

/**
 * @brief Collapse the quotations in the token list into word tokens
 * @param single boolean indicating type of quotation to collapse
 * @param list linked list of tokens we are operating on
 * @return linked list of tokens after the collapse of the desired quotations
 */
t_token *collapse_quotes(t_bool single, t_token *list) {
	t_token *iterator;
	t_token *open_quote;
	t_token *close_quote;
	t_token *remainder;
	t_token *newtoken;
	enum e_token_type qtype;
	enum e_token_type otype;
	t_bool enclosed;

	if (single)
	{
		qtype = SINGLE_QUOTE;
		otype = DOUBLE_QUOTE;
	}
	else
	{
		qtype = DOUBLE_QUOTE;
		otype = SINGLE_QUOTE;
	}
	iterator = list;
	enclosed = FALSE;
	while (iterator)
	{
		while (iterator && (iterator->type != qtype || enclosed))
		{
			if (iterator->type == otype)
				enclosed = !enclosed;
			iterator = iterator->next;
		}
		if (!iterator)
			return (list);
		open_quote = iterator;
		iterator = open_quote->prev;
		if (iterator)
			iterator->next = NULL;
		open_quote->prev = NULL;
		close_quote = open_quote->next;
		while (close_quote && close_quote->type != qtype)
			close_quote = close_quote->next;
		if (!close_quote) {
			clear_tokenlist(&list);
			list = malloc(sizeof(t_token));
			*list = (t_token){ERROR, "UNCLOSED QUOTATION", NULL, NULL};
			return (list);
		}
		remainder = close_quote->next;
		close_quote->next = NULL;
		if (remainder)
			remainder->prev = NULL;
		newtoken = merge_quotation_tokens(open_quote);
		if (!iterator)
		{
			list = newtoken;
			if (!remainder)
				return (list);
		}
		clear_tokenlist(&open_quote);
		if (iterator)
			iterator->next = newtoken;
		newtoken->prev = iterator;
		newtoken->next = remainder;
		if (remainder)
			remainder->prev = newtoken;
		if (!newtoken->prev)
			list = newtoken;
		iterator = remainder;
	}
	return list;
}
