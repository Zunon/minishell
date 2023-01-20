/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:18:51 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/04 18:48:07 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/dictionary.h"

/**
 * @brief					Create a Dictionary and allocate necessary memory
 *
 * @param s					Capacity of Dictionary
 * @return t_dict*			Newly created Dictionary of size s
 */
t_dict	*create_dict(int s)
{
	t_dict	*dict;
	int		i;

	i = 0;
	if (s <= 0)
		return (NULL);
	dict = malloc(sizeof(t_dict));
	if (!dict)
		return (NULL);
	dict->table = malloc (sizeof(t_pair *) * s);
	if (!dict->table)
		return (NULL);
	while (i < s)
	{
		dict->table[i] = (NULL);
		i++;
	}
	dict->capacity = s;
	dict->size = 0;
	return (dict);
}

/**
 * @brief 					Retrieve a key-value pair from the Dictionary with
 * 							a specific key
 *
 * @param t					Dictionary to search in
 * @param key				Key to look for
 * @return t_pair*			Key value pair that matches the given key on sucess,
 * 							NULL on failed search
 */
t_pair	*retrieve_from_dict(t_dict *t, char *key)
{
	int	index;

	index = 0;
	while (index <= t->capacity)
	{
		if (t->table[index] && ft_strncmp(t->table[index]->key, key, 1000000)
			== 0)
			return (t->table[index]);
		index = (index + 1) % t->capacity;
		if (index == 0)
			return (NULL);
	}
	return (NULL);
}

/**
 * @brief					Insert a key-value pair into the Dictionary
 *
 * @param t					Dictionary to insert to
 * @param key				Key of new entry
 * @param value				Value of new entry
 */
void	insert_into_dict(t_dict **t, char *key, char *value)
{
	int		index;
	t_pair	*exists;

	index = 0;
	exists = retrieve_from_dict(*t, key);
	if (exists && value)
	{
		free(exists->value);
		exists->value = ft_strdup(value);
		return ;
	}
	if ((*t)->size == (*t)->capacity)
		*t = resize_dict(*t, 2 *(*t)->capacity + 1);
	while ((*t)->table[index])
		index = (index + 1) % (*t)->capacity;
	(*t)->table[index] = malloc(sizeof(t_pair));
	if (!(*t)->table[index])
		return ;
	(*t)->table[index]->key = ft_strdup(key);
	(*t)->table[index]->value = NULL;
	if (value)(*t)->table[index]->value = ft_strdup(value);
	(*t)->size++;
}

/**
 * @brief					Remove a specific key-value pair from the Dictionary
 *
 * @param t					Dictionary to search in
 * @param key				Key of Dictionary entry to delete
 */
void	remove_from_dict(t_dict *t, char *key)
{
	int	index;

	index = 0;
	while (index <= t->capacity)
	{
		if (t->table[index] && ft_strncmp(t->table[index]->key, key,
				ft_strlen(key)) == 0)
		{
			destroy_pair(t->table[index]);
			t->table[index] = NULL;
			return ;
		}
		index = (index + 1) % t->capacity;
		if (index == 0)
			return ;
	}
}

/**
 * @brief					Function to resize a Dictionary on reaching full capacity
 * 							Not to be called by user - will be indirectly called whenever needed
 * 							automatically.
 *
 * @param t
 * @param newCapacity		New capacity of Dictionary
 * @return t_dict*			New Dictionary after resizing
 */
t_dict	*resize_dict(t_dict *t, int newCapacity)
{
	int		i;
	t_dict	*new_table;

	i = 0;
	if (newCapacity < 0 || newCapacity <= t->capacity)
		return (NULL);
	t->capacity = newCapacity;
	new_table = create_dict(newCapacity);
	if (!new_table)
		return (NULL);
	while (i < t->size)
	{
		insert_into_dict(&new_table, t->table[i]->key, t->table[i]->value);
		i++;
	}
	destroy_dict(t);
	return (new_table);
}
