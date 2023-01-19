/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:33:22 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/04 21:49:13 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/dictionary.h"


/**
 * @brief					Function to print a key-value pair
 *
 * @param p					{key : value} pair to print
 */
void	print_pair(t_pair *p)
{
	if (!p)
		return ;
	ft_putstr_fd(p->key, STDOUT_FILENO);
	ft_putstr_fd("=", STDOUT_FILENO);
	ft_putstr_fd(p->value, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

/**
 * @brief					Function to print all entries in a Dictionary
 *
 * @param t					Dictionary to print
 */
void	print_dict(t_dict *t)
{
	int	i;

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
 * @brief					Duplicate a dictionary
 *
 * @param dict				Dictionary to duplicate
 * @return t_dict*			Pointer to duplicated dictionary
 */
t_dict	*duplicate_dictionary(t_dict *dict)
{
	int		i;
	t_dict	*new_table;

	i = 0;
	new_table = create_dict(dict->capacity);
	new_table->capacity = dict->capacity;
	if (!new_table)
		return (NULL);
	while (i < dict->size)
	{
		insert_into_dict(&new_table, dict->table[i]->key,
			dict->table[i]->value);
		i++;
	}
	return (new_table);
}

/**
 * @brief					Function to sort a dictionary according to the function
 * 							desired
 *
 * @param dict				Dictionary to sort
 * @param compare			Function used to compare keys of a dictionary
 * @return t_dict*			Pointer to sorted duplicated dictionary
 */
t_dict	*sort_dictionary(t_dict *dict, int (*compare)(const char *,
	const char *, size_t))
{
	int		i;
	int		j;
	t_pair	*temp;
	t_dict	*duped_dict;

	i = 0;
	duped_dict = duplicate_dictionary(dict);
	while (duped_dict->table[i + 1])
	{
		j = i + 1;
		while (duped_dict->table[j])
		{
			if (compare(duped_dict->table[i]->key,
					duped_dict->table[j]->key, 1024) > 0)
			{
				temp = duped_dict->table[i];
				duped_dict->table[i] = duped_dict->table[j];
				duped_dict->table[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (duped_dict);
}

/**
 * @brief					Convert a dictionary into an array of strings
 *
 * @param dict				Dictionary to convert
 * @return char**			Array of strings containing all key-value pairs
 */
char	**dict_to_string_arr(t_dict *dict)
{
	char	*temp;
	char	**strs;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!dict || !dict->table)
		return (NULL);
	strs = malloc(sizeof(char *) * (dict->size + 1));
	while (i < dict->capacity)
	{
		if (dict->table[i])
		{
			temp = ft_strjoin(dict->table[i]->key, "=");
			strs[j] = ft_strjoin(temp, dict->table[i]->value);
			free(temp);
			j++;
		}		
		i++;
	}
	strs[j] = NULL;
	return (strs);
}
