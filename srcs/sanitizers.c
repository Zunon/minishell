/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:00:02 by kalmheir          #+#    #+#             */
/*   Updated: 2023/01/17 00:00:07 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*discard_dollar(t_token *list)
{
	t_token				*iterator;
	enum e_token_type	status;

	iterator = list;
	status = ERROR;
	while (iterator)
	{
		if (status == ERROR && iterator->type == VARIABLE
			&& !((iterator->contents)[1]))
			del_token(&list, &iterator);
		else if (iterator->type == VARIABLE && !((iterator->contents)[1]))
			iterator->type = WORD;
		else if (iterator->type == SINGLE_QUOTE
			|| iterator->type == DOUBLE_QUOTE)
		{
			if (status == iterator->type)
				status = ERROR;
			else if (status == ERROR)
				status = iterator->type;
			iterator = iterator->next;
		}
		else
			iterator = iterator->next;
	}
	return (list);
}

t_token	*split_words_on_whitespace(t_token *list)
{
	t_token	*iterator;

	iterator = list;
	while (iterator)
	{
		if (iterator->type == WORD && ft_strchr(iterator->contents, ' '))
			splice_tokens(&list, &iterator);
		else
			iterator = iterator->next;
	}
	return (list);
}

/**
 * @brief Prune whitespace out of the token list
 * @param list linked list of tokens
 * @return pruned list
 */
t_token	*discard_whitespace(t_token *list)
{
	t_token	*iterator;

	iterator = list;
	while (iterator)
	{
		if (iterator->type == WHITESPACE || !(iterator->contents))
			del_token(&list, &iterator);
		else
			iterator = iterator->next;
	}
	return (list);
}

/**
 * @brief Expand all variable tokens and replace them with the respective word
 * @param list linked list of all tokens
 * @return list but with no variable tokens
 */
t_token	*expand_variables(t_token *list)
{
	t_token	*iterator;
	char	*temp;

	iterator = list;
	while (iterator)
	{
		if (iterator->type == VARIABLE)
		{
			iterator->type = WORD;
			temp = iterator->contents;
			iterator->contents = expand(iterator->contents + 1);
			free(temp);
		}
		iterator = iterator->next;
	}
	return (list);
}

t_token	*disquote(t_token *list)
{
	t_token	*iterator;

	iterator = list;
	while (iterator)
	{
		if (iterator->type == QUOTED)
			iterator->type = WORD;
		iterator = iterator->next;
	}
	return (list);
}
