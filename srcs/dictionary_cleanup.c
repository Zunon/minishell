/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_cleanup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 21:21:53 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/04 21:52:03 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/dictionary.h"

/**
 * @brief 					Function to free allocated memory of a given key-value pair
 *
 * @param p					Key value pair to destroy
 */
void destroy_pair(t_pair *p)
{
	if (!p)
		return;
	if (p->key)
		free(p->key);
	if (p->value)
		free(p->value);
	free(p);
}

/**
 * @brief					Function to free all allocated memory of a Dictionary
 *
 * @param t					Dictionary to destroy
 */
void destroy_dict(t_dict *t)
{
	int i;

	i = 0;
	if (!t || !t->table || t->size == 0)
		return;
	while (i < t->size)
	{
		destroy_pair(t->table[i]);
		i++;
	}
	free(t->table);
	t->table = NULL;
	t->size = 0;
	free(t);
}