/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_funcs0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:42:06 by kalmheir          #+#    #+#             */
/*   Updated: 2022/06/26 17:38:32 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/**
 * @brief Finds the first occurence of the given character in the given string.
 *
 * @param s	Start of string to be searched through.
 * @param c	Character to be searched for.
 * @return Pointer to the first occurence of c in s.
 */
char	*ft_strchr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (!c)
		return ((char *)(s + i));
	return (0);
}

/**
 * @brief Counts the number of bytes in a string.
 *
 * @param s	String to be iterated through.
 * @return Size of string in terms of bytes.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

/**
 * @brief Finds the last occurence of the given character in the given string.
 *
 * @param s	Start of string to be searched through.
 * @param c	Character to be searched for.
 * @return Pointer to the last occurence of c in s.
 */
char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*result;

	i = 0;
	result = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			result = (char *)(s + i);
		i++;
	}
	if (!c)
		return ((char *)(s + i));
	return (result);
}

/**
 * @brief Returns the lowercase representation of the given character.
 *
 * @param c	Character to be transformed.
 * @return Lowercase version of c if c is uppercase, c otherwise.
 */
char	ft_tolower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 0x20);
	return (c);
}

/**
 * @brief Returns the uppercase representation of the given character.
 *
 * @param c	Character to be transformed.
 * @return Uppercase version of c if c is lowercase, c otherwise.
 */
char	ft_toupper(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 0x20);
	return (c);
}
