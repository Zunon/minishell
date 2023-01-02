/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 11:58:02 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/02 10:35:29 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
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

typedef struct s_hash_table{
    int size;
    int capacity;
    t_pair **table;
} t_hash_table;

t_hash_table *create_ht(int s);
void destroy_ht(t_hash_table *t);
void destroy_pair(t_pair *p);
t_hash_table *resize_ht(t_hash_table *t, int);
t_pair *retrieve_from_ht(t_hash_table *t, char *key);
void insert_into_ht(t_hash_table **t, char* key, char *value);
void remove_from_ht(t_hash_table *t, char *key);
void print_ht(t_hash_table *t);
int hash(char *);


#endif