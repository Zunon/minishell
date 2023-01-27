/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_funcs0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:01:04 by kalmheir          #+#    #+#             */
/*   Updated: 2022/06/26 19:12:19 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/**
 * @brief Parses a string into an integer. Skipping over the initial whitespace
 * portion. Then skipping one plus or minus sign, then parsing the next
 * numerical portion into an integer.
 * @param str	String to be parsed.
 * @return Integer parsed from str.
 */
int	ft_atoi(const char *str)
{
	char	sign;
	size_t	i;
	int		result;
	int		dtc;

	result = 0;
	i = -1;
	sign = 1;
	while (ft_iswhitespace(str[++i]))
		;
	while (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -sign;
	while (ft_isdigit(str[i]))
	{
		dtc = result;
		result *= 10;
		result += (1 * sign) * (str[i] - '0');
		if ((dtc ^ result) & 0x80000000 && dtc != 0)
			return ((dtc < 0) - 1);
		i++;
	}
	return (result);
}

/**
 * @brief Sets each byte in a memory region to 0x00.
 *
 * @param s	Start of memory region.
 * @param n	Length of memory region.
 */
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0x00, n);
}

/**
 * @brief Dynamically allocates a memory region for a given amount of items and
 * the size of each of those items.
 * @param count	Number of items to allocate for.
 * @param size	Size of each item in terms of bytes.
 * @return Start of the memory region allocated. Null on allocation failure.
 */
void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*area;
	size_t			total_size;
	size_t			i;

	total_size = size * count;
	i = 0;
	area = malloc(total_size);
	if (!area)
		return (0);
	while (i < total_size)
		area[i++] = 0;
	return ((void *)area);
}

/**
 * @brief Helper function for strnstr. Used on partial matches that led to a
 * mismatch to recent the iterator variables and the boolean representing the
 * beginning.
 * @param m			Pointer to iterating variable of the haystack.
 * @param n 		Pointer to iterating variable of the needle.
 * @param startpos	Where the beginning of a partial match is, negative value on
 * a 'no match yet'.
 */
void	reset(char **haystack, size_t *m, size_t *n, char **startpos)
{
	*m = 0;
	*n = *startpos - *haystack;
	*startpos = 0;
}

/**
 * @brief Recursive expontiating function.
 *
 * @param nb	Number to be raised to the given power.
 * @param power	The exponent.
 * @return nb^power
 */
int	ft_pow(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_pow(nb, power - 1));
}
