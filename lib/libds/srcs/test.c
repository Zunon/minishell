/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:27:36 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/02 11:09:52 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file test.c
 * @author Radi Aman Riyas (radiriyas@gmail.com)
 * @brief	Test code to test hashtable implementation
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../hashtable.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	totlength;
	size_t	actual_length;
	char	*result;

	if (!s)
		return (0);
	totlength = ft_strlen(s);
	if (start >= totlength)
	{
		result = malloc(sizeof(char));
		if (!result)
			return (0);
		result[0] = 0;
		return (result);
	}
	if (totlength > len)
		actual_length = len;
	else
		actual_length = totlength - start;
	result = malloc((actual_length + 1) * sizeof(char));
	if (!result)
		return (0);
	ft_strlcpy(result, s + start, actual_length + 1);
	return (result);
}

int find_pos(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int main(int argc, char **argv, char **envp)
{
    t_hash_table *ht;
    int i;

    i = 0;
    ht = create_ht(5);
    int pos;
    char *key, *value;
    while (envp[i])
    {
        pos = find_pos(envp[i], '=');
        key = ft_substr(envp[i], 0, pos);
        value = ft_substr(envp[i], pos + 1, 10000000);
        insert_into_ht(&ht, key, value);
        free(key);
        free(value);
        i++;
    }
	print_ht(ht);
    i = 0;
    char *strr = malloc(25);
	printf("Retrieve tests - enter 6 env vars to look for:\n");
    while (i < 6)
    {
        scanf("%s", strr);
        t_pair *p = retrieve_from_ht(ht, strr);
        if (p)
            printf("key = %s and value = %s\n", p->key, p->value);
        i++;
    }
	free(strr);
	key = malloc(20);
	value = malloc(20);
	i = 0;
	printf("Insert tests - enter 6 env vars to add to ht:\n");
	while (i < 6)
	{
		scanf("%s", key);
		scanf("%s", value);
		insert_into_ht(&ht, key, value);
		t_pair *p = retrieve_from_ht(ht, strr);
		if (p)
			printf("\nnew key = %s and value = %s\n\n", p->key, p->value);
		i++;
	}
	print_ht(ht);
	printf("Deletion tests - enter 4 env vars to delete from ht:\n");
	i = 0;
	while (i < 4)
	{
		scanf("%s", key);
		remove_from_ht(ht, key);
		t_pair *p = retrieve_from_ht(ht, strr);
		if (p)
			printf("\nnew key = %s and value = %s\n\n", p->key, p->value);
		else
			printf("\nSuccesfully deleted!\n");
		i++;
	}
	print_ht(ht);
	destroy_ht(ht);
	free(key);
	free(value);
    return 0;
}