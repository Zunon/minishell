/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:18:51 by rriyas            #+#    #+#             */
/*   Updated: 2022/12/31 12:18:51 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hashtable.h"

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

t_pair *retrieve_from_ht(t_hash_table *t, char *key)
{
    int index;

    index = 0;
    while (t->table[index] && ft_strncmp(t->table[index]->key, key, 1000000) != 0)
    {
        index = (index + 1) % t->capacity;
        if (index == 0)
            return NULL;    
    }
    return t->table[index];
}

void insert_into_ht(t_hash_table **t, char* key, char* value)
{
    int index;

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

void remove_from_ht(t_hash_table *t, char* key)
{
    int index;

    index = 0;
    while (ft_strncmp(t->table[index]->key, key, ft_strlen(key)) != 0)
    {
        index = (index + 1) % t->capacity;
        if (index == 0)
            return ;
    }
    free(t->table[index]);
    t->table[index] = NULL;
}


int hash(char * key)
{
    int h;
    int i;

    i = -1;
    while (key[++i])
        h = h + (31 * key[i]); 
    if (h < 0)
        h = -h;
    return (h);
}