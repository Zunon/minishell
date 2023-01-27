/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_funcs2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 13:33:22 by kalmheir          #+#    #+#             */
/*   Updated: 2022/06/26 17:58:56 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/**
 * @brief Counts the length of a string until a specific character is
 * encountered.
 * @param str	Pointer to the beginning of the string.
 * @param sep	Word terminator.
 * @return Length of str until sep.
 */
int	word_len(char const *str, char sep)
{
	int	n;

	n = 0;
	while (str[n] && str[n] != sep)
		n++;
	return (n);
}

/**
 * @brief Counts the amount of words in a given string using a given word
 * separator.
 * @param str	String to be iterated through.
 * @param sep	Separator to terminate words.
 * @return Number of words within the string.
 */
int	count_words(char const *str, char sep)
{
	if (!*str)
		return (0);
	while (*str && *str == sep)
		str++;
	if (!*str)
		return (0);
	while (*str && *str != sep)
		str++;
	if (!*str)
		return (1);
	else
		return (1 + count_words(str, sep));
}

char	**returner(char const *str)
{
	char	**result;

	if (!str)
	{
		result = ft_calloc(1, sizeof(char *));
		if (!result)
			return (0);
		result[0] = 0;
		return (result);
	}
	else
	{
		result = ft_calloc(2, sizeof(char *));
		if (!result)
			return (0);
		result[0] = ft_strdup(str);
		result[1] = 0;
		return (result);
	}
}

/**
 * @brief Splits a string into an array of strings, by dividing the string when
 * encountering a specific character.
 * @param s	String to transform into an array of strings.
 * @param c	Word separator.
 * @return Null-terminated array of strings which are all portions of s.
 */
char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;
	int		i;

	if (!s || !*s)
		return (returner(0));
	if (!c)
		return (returner(s));
	words = count_words(s, c);
	i = 0;
	result = ft_calloc((words + 1), sizeof(char *));
	if (!result)
		return (0);
	while (i < words)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		result[i++] = ft_substr(s, 0, word_len(s, c));
		s += word_len(s, c);
	}
	result[i] = 0;
	return (result);
}

/**
 * @brief Merges two strings into one larger string.
 *
 * @param s1	First string to join.
 * @param s2	Second string to join.
 * @return The combined string out of s1 and s2.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return ((char *)s2);
	else if (!s2)
		return ((char *)s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = ft_calloc((len1 + len2 + 1), sizeof(char));
	if (!result)
		return (0);
	result[0] = 0;
	ft_strlcat(result, s1, len1 + len2 + 1);
	ft_strlcat(result, s2, len1 + len2 + 1);
	return (result);
}
