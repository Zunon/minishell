/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:28:13 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/14 00:45:10 by rriyas           ###   ########.fr       */
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
		return (ft_itoa(zundra.status_code));
	}
	pair = retrieve_from_dict(zundra.env_mngr, word);
	if (pair)
		result = ft_strdup(pair->value);
	else
		result = ft_strdup("");
	return (result);
}
