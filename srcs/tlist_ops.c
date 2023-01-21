/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlist_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:59:46 by kalmheir          #+#    #+#             */
/*   Updated: 2023/01/21 16:14:10 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*token_split(char *string)
{
	char	**array;
	int		iterator;
	t_token	*result;
	t_token	*tracer;

	if (!string || !*string)
		return (NULL);
	array = ft_split(string, ' ');
	iterator = 0;
	result = ft_calloc(1, sizeof(t_token));
	*result = (t_token){WORD, ft_strdup(array[iterator]), NULL, NULL};
	tracer = result;
	while (array[++iterator])
	{
		tracer->next = ft_calloc(1, sizeof(t_token));
		*(tracer->next) = (t_token){WORD, ft_strdup(array[iterator]), NULL,
			tracer};
		tracer = tracer->next;
	}
	iterator = 0;
	while (array[iterator])
		free(array[iterator++]);
	free(array);
	return (result);
}

t_token	*token_last(t_token *list)
{
	t_token	*iterator;

	iterator = list;
	while (iterator->next)
		iterator = iterator->next;
	return (iterator);
}

/**
 * @brief Merge the list given to it into one big word token
 * @param quote linked list of tokens to be merged
 * @return the word token with the merged contents
 */
t_token	*merge_quotation_tokens(t_token *quote)
{
	char				*final_content;
	enum e_token_type	type;
	t_token				*iterator;
	t_token				*result;

	final_content = ft_strdup("");
	type = quote->type;
	iterator = quote->next;
	while (iterator->type != type)
	{
		final_content = join_and_free(final_content, iterator->contents, TRUE,
				FALSE);
		iterator = iterator->next;
	}
	result = ft_calloc(1, sizeof(t_token));
	*result = (t_token){QUOTED, final_content};
	return (result);
}

void	print_token_type(const t_token *list)
{
	if (list->type == VARIABLE)
		ft_printf("VARIABLE, ");
	else if (list->type == WORD)
		ft_printf("WORD, ");
	else if (list->type == REDIRECTION)
		ft_printf("REDIRECTION, ");
	else if (list->type == PIPE)
		ft_printf("PIPE, ");
	else if (list->type == WHITESPACE)
		ft_printf("WHITESPACE, ");
	else if (list->type == SINGLE_QUOTE)
		ft_printf("SINGLE_QUOTE, ");
	else if (list->type == DOUBLE_QUOTE)
		ft_printf("DOUBLE_QUOTE, ");
	else if (list->type == ERROR)
		ft_printf("ERROR, ");
	else if (list->type == QUOTED)
		ft_printf("QUOTED, ");
}

void	print_tokens(t_token *list)
{
	ft_printf("HEAD\n");
	while (list)
	{
		ft_printf("TYPE: ");
		print_token_type(list);
		ft_printf("CONTENTS: %s, PREV: %p, NEXT: %p\n", list->contents,
			list->prev, list->next);
		list = list->next;
	}
	ft_printf("TAIL\n");
}
