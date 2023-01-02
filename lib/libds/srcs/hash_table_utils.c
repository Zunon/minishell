/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:33:22 by rriyas            #+#    #+#             */
/*   Updated: 2022/12/31 12:33:22 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hashtable.h"

void destroy_pair(t_pair *p)
{
    if (!p)
        return ;
    if (p->key)
        free(p->key);
    if (p->value)
        free(p->value);
    free(p);
}

void destroy_ht(t_hash_table *t)
{
    int i;

    i = 0;
    if (!t || !t->table || t->size == 0)
        return ;
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

void print_pair(t_pair *p)
{
    if (!p)
        return ;
    ft_putstr_fd(p->key, STDOUT_FILENO);
    ft_putstr_fd("=", STDOUT_FILENO);
    ft_putstr_fd(p->value, STDOUT_FILENO);
    ft_putstr_fd("\n", STDOUT_FILENO);
}
void print_ht(t_hash_table *t)
{
    int i;

    i = 0;
    if (!t || t->size == 0)
        return ;
    while (i <= t->size)
    {
        print_pair(t->table[i]);
        i++;
    }
}

t_hash_table * resize_ht(t_hash_table *t, int newSize)
{
    int i;

    t_hash_table *new_table;
    i = 0;
    write(1, "sup", 3);
    if (newSize < 0 || newSize <= t->capacity)
        return (NULL);
    t->capacity = newSize;
    new_table = create_ht(newSize);
    if (!new_table)
        return (NULL);
    while (i < t->size)
    {
        insert_into_ht(&new_table, t->table[i]->key, t->table[i]->value);
        i++;
    }
    destroy_ht(t);
    return (new_table);
}