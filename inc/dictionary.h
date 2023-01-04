/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 11:58:02 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/04 21:49:22 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DICTIONARY_H
#define FT_DICTIONARY_H

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

typedef struct s_dict {
    int size;
    int capacity;
    t_pair **table;
} t_dict;

//dictionary.c
t_dict *create_dict(int s);
t_pair *retrieve_from_dict(t_dict *t, char *key);
void insert_into_dict(t_dict **t, char *key, char *value);
void remove_from_dict(t_dict *t, char *key);
t_dict *resize_dict(t_dict *t, int newCapacity);

//dictionary_utils.c
void print_pair(t_pair *p);
void print_dict(t_dict *t);
t_dict *duplicate_dictionary(t_dict *dict);
t_dict *sort_dictionary(t_dict *dict, int (*compare)(char *, char *, size_t));
char **dict_to_string_arr(t_dict *dict);

//dictionary_cleanup.c
void destroy_pair(t_pair *p);
void destroy_dict(t_dict *t);

#endif