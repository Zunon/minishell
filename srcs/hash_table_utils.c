/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:33:22 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/02 11:10:10 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/hashtable.h"

/**
 * @brief 					Function to free allocated memory of a given key-value pair
 *
 * @param p
 */
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

/**
 * @brief					Function to free all allocated memory of a hash table
 *
 * @param t					Hash table to destroy
 */
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

/**
 * @brief					Function to print a key-value pair
 *
 * @param p					{key : value} pair to print
 */
void print_pair(t_pair *p)
{
    if (!p)
        return ;
    ft_putstr_fd(p->key, STDOUT_FILENO);
    ft_putstr_fd("=", STDOUT_FILENO);
    ft_putstr_fd(p->value, STDOUT_FILENO);
    ft_putstr_fd("\n", STDOUT_FILENO);
}

/**
 * @brief					Function to print all entries in a hash table
 *
 * @param t					Hash table to print
 */
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

/**
 * @brief					Function to resize a hash tabel on reaching full capacity
 * 							Not to be called by user - will be indirectly called whenever needed
 * 							automatically.
 *
 * @param t
 * @param newCapacity		New capacity of hash table
 * @return t_hash_table*	New hash table after resizing
 */
t_hash_table * resize_ht(t_hash_table *t, int newCapacity)
{
    int i;

    t_hash_table *new_table;
    i = 0;
    write(1, "sup", 3);
    if (newCapacity < 0 || newCapacity <= t->capacity)
        return (NULL);
    t->capacity = newCapacity;
    new_table = create_ht(newCapacity);
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