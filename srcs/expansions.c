/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:28:13 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/10 19:48:23 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief			Handle environment variable expansion (if any)
 *
 * @param words		Linked list of words that may or may not have expansions
 */
void expansion_handler(t_word_list *words)
{
	t_pair *pair;
	while (words)
	{
		while (words->curr_word_desc->dollar_present && words->curr_word_desc->quoted)
		{
			pair = retrieve_from_dict(zundra.env_mngr, words->curr_word_desc->word);
			if (pair)
			{
				free(words->curr_word_desc->word);
				words->curr_word_desc->word = ft_strdup(pair->value);
				if (pair->value && pair->value[0] == '$')
					words->curr_word_desc->dollar_present = 1;
			}
			free(words->curr_word_desc->word);
			words->curr_word_desc->word = ft_strdup("");
			words->curr_word_desc->dollar_present = 0;
		}
		words = words->next;
	}
}
