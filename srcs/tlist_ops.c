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
	*result = (t_token){QUOTED, final_content, NULL, NULL};
	return (result);
}
