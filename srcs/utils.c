/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:41:42 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/27 19:56:58 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	length_of_arr(char **split)
{
	size_t	len;

	len = 0;
	while (split[len])
		len++;
	return (len);
}

void	freesplit(char **split)
{
	size_t	iterator;

	iterator = 0;
	while (split[iterator])
		free(split[iterator++]);
	free(split);
}
