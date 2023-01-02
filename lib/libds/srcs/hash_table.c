/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:18:51 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/02 11:17:09 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hashtable.h"

/**
 * @brief					Create a hash table and allocate necessary memory
 *
 * @param s					Capacity of hash table
 * @return t_hash_table*	Newly created hash tabel of size s
 */
t_hash_table *create_ht(int s)
{
    t_hash_table *hash_table;
    int i;

    i = 0;
    if (s <= 0)
        return NULL;
    hash_table = malloc(sizeof(t_hash_table));
    if (!hash_table)
        return NULL;
    hash_table->table = malloc (sizeof(t_pair*) * s);
    if (!hash_table->table)
        return NULL;
    while (i < s)
    {
        hash_table->table[i] = NULL;
        i++;
    }
    hash_table->capacity = s;
    hash_table->size = 0;
    return hash_table;
}

/**
 * @brief 					Retrieve a key-value pair from the hash table with specific key
 *
 * @param t					Hash table to search in
 * @param key				Key to look for
 * @return t_pair*			Key value pair that matches the given key on sucess, NULL on failed search
 */
t_pair *retrieve_from_ht(t_hash_table *t, char *key)
{
    int index;

    index = 0;
    while (index <= t->capacity)
    {
		if (t->table[index] && ft_strncmp(t->table[index]->key, key, 1000000) == 0)
			return t->table[index];
		index = (index + 1) % t->capacity;
		if (index == 0)
			return (NULL);
    }
	return (NULL);
}

/**
 * @brief					Insert a key-value pair into the hash table
 *
 * @param t					Hash table to insert to
 * @param key				Key of new entry
 * @param value				Value of new entry
 */
void insert_into_ht(t_hash_table **t, char* key, char* value)
{
    int index;
	t_pair *exists;

	exists = retrieve_from_ht(*t, key) ;
	if (exists)
	{
		free(exists->value);
		exists->value = ft_strdup(value);
		return ;
	}
    if ((*t)->size == (*t)->capacity)
        *t = resize_ht(*t, 2 *(*t)->capacity + 1);
    index = (*t)->size % (*t)->capacity;
    while ((*t)->table[index])
        index = (index + 1) % (*t)->capacity;
    (*t)->table[index] = malloc(sizeof(t_pair));
    if (!(*t)->table[index])
        return ;
    (*t)->table[index]->key = ft_strdup(key);
    (*t)->table[index]->value = ft_strdup(value);
    (*t)->size++;
}

/**
 * @brief					Remove a specific key-value pair from the hash table
 *
 * @param t					Hash table to search in
 * @param key				Key of hash table entry to delete
 */
void remove_from_ht(t_hash_table *t, char* key)
{
    int index;

    index = 0;
	while (index <= t->capacity)
	{
		if (t->table[index] && ft_strncmp(t->table[index]->key, key, ft_strlen(key)) == 0)
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