/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_funcs3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:40:31 by kalmheir          #+#    #+#             */
/*   Updated: 2022/06/26 18:10:11 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/**
 * @brief Iterates through a string by applying a function on every character.
 *
 * @param s	String to be iterated through.
 * @param f	Function to apply on each character, to be given its index and a
 * pointer to that character.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[++i - 1])
		(*f)(i - 1, &s[i - 1]);
}

/**
 * @brief Builds a new string based on a mapping of a given string and a
 * function to be applied on every character.
 *
 * @param s	String to be iterated through.
 * @param f	Function to apply on each character, to be given its index and a
 * pointer to that character.
 * @return Newly allocated string which is a mapping of s mapped with f.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			length;
	unsigned int	i;
	char			*result;

	if (!s || !f)
		return (0);
	length = ft_strlen(s);
	result = ft_calloc(length + 1, sizeof(char));
	if (!result)
		return (0);
	i = -1;
	while (++i < length)
		result[i] = (*f)(i, s[i]);
	result[i] = 0;
	return (result);
}

/**
 * @brief Trims specific characters away from a string and returns the trimmed
 * substring.
 * @param s1	String to be trimmed.
 * @param set	String representing the set of characters to be trimmed out of
 * the boundaries of s1.
 * @return Newly allocated substring of s1 not containing characters from set at
 * the boundaries.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start_i;
	size_t	end_i;

	if (!s1)
		return (0);
	if (!set)
		return ((char *)s1);
	start_i = 0;
	end_i = ft_strlen(s1) - 1;
	while (ft_strchr(set, (int)s1[start_i]))
		start_i++;
	while (ft_strchr(set, (int)s1[end_i]))
		end_i--;
	return (ft_substr(s1, start_i, end_i - start_i + 1));
}

/**
 * @brief Allocates a string which is a substring of the given string.
 *
 * @param s		String from which to allocate a substring from.
 * @param start	The index in which the substring should start.
 * @param len	Length of the substring.
 * @return Newly allocated substring of s.
 */
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
		result = ft_strdup("");
		if (!result)
			return (0);
		result[0] = 0;
		return (result);
	}
	if (totlength > len)
		actual_length = len;
	else
		actual_length = totlength - start;
	result = ft_calloc((actual_length + 1), sizeof(char));
	if (!result)
		return (0);
	ft_strlcpy(result, s + start, actual_length + 1);
	return (result);
}

char	*join_and_free(char *left, char *right, t_bool free_left,
			t_bool free_right)
{
	char	*result;

	result = ft_strjoin(left, right);
	if (free_left)
		free(left);
	if (free_right)
		free(right);
	return (result);
}
