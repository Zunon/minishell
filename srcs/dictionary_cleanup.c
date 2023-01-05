/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_cleanup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 21:21:53 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/05 18:35:46 by rriyas           ###   ########.fr       */
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

static int find_pos(char *s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_dict *generate_env_manager(char **envp)
{
	t_dict *env_manager;
	int i;
	char *key;
	char *value;
	int pos;

	i = 0;
	env_manager = create_dict(25);
	while (envp[i])
	{
		pos = find_pos(envp[i], '=');
		if (pos != -1)
		{
			key = ft_substr(envp[i], 0, pos);
			value = ft_substr(envp[i], pos + 1, 10000000);
		}
		insert_into_dict(&env_manager, key, value);
		free(key);
		free(value);
		i++;
	}
	return (env_manager);
}