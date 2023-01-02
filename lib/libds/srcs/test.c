/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:27:36 by rriyas            #+#    #+#             */
/*   Updated: 2022/12/31 16:27:36 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
unsigned int x = 0;
int main(int argc, char **argv, char **envp)
{
    t_hash_table *ht;
    int i;

    i = 0;
    ht = create_ht(5);
    int pos;
    char *key, *value;
	int fd = open("sup.txt", O_WRONLY | O_CREAT, 0777);

    while (envp[i])
    {
        pos = find_pos(envp[i], '=');
        key = ft_substr(envp[i], 0, pos);
        value = ft_substr(envp[i], pos+1, 10000000);
        ft_putstr_fd(envp[i], fd);
        write(fd, "\n", 1);
        insert_into_ht(&ht, key, value);
        free(key);
        free(value);
        i++;
    }
    close(fd);
    print_ht(ht);
    i = 0;
    char *lookfor = malloc(25);
    // while (i < 6)
    // {
    //     scanf("%s", lookfor);
    //     t_pair *p = retrieve_from_ht(ht, lookfor);
    //     if (p)
    //         printf("\nkey = %s and value = %s", p->key, p->value);
    //     i++;
    // }
    destroy_ht(ht);
    free(lookfor);
    return 0;
}