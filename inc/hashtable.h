/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 11:58:02 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/02 11:42:16 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

#include <unistd.h>
#include <stdlib.h>
#include "../lib/libft/libft.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

typedef struct s_pair{
    char *key;
    char *value;
}t_pair;

typedef struct s_hash_table {
    int size;
    int capacity;
    t_pair **table;
} t_hash_table;

// hash_table.c
t_hash_table *create_ht(int s);
t_pair *retrieve_from_ht(t_hash_table *t, char *key);
void insert_into_ht(t_hash_table **t, char *key, char *value);
void remove_from_ht(t_hash_table *t, char *key);

//hash_table_utils.c
void destroy_pair(t_pair *p);
void destroy_ht(t_hash_table *t);
void print_pair(t_pair *p);
void print_ht(t_hash_table *t);
t_hash_table *resize_ht(t_hash_table *t, int newCapacity);


#endif