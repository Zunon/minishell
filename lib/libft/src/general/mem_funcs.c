/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:13:50 by kalmheir          #+#    #+#             */
/*   Updated: 2022/06/26 16:02:40 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/**
 * @brief Searches for a specific byte value within a memory region.
 *
 * @param s	Start of memory region.
 * @param c	Byte value to be searched for.
 * @param n	Length of memory region.
 * @return Pointer to the first occurence of c found within region. Null
 * otherwise.
 */
void	*ft_memchr(const void *s, t_byte c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((t_byte *)s)[i] == (t_byte)c)
			return ((void *)s + i);
		i++;
	}
	return (0);
}

/**
 * @brief Compares between the absolute numerical value of two memory regions.
 *
 * @param s1	Start of the first memory region.
 * @param s2	Start of the second memory region.
 * @param n		How many pairs of bytes to compare at the most.
 * @return	Positive number if s1 is greater than s2. Negative number if s2 is
 * greater than s1. Zero if they're equal up to n bytes.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((t_byte *)s1)[i] != ((t_byte *)s2)[i])
			break ;
		i++;
	}
	if (i == n)
		return (0);
	return (((t_byte *)s1)[i] - ((t_byte *)s2)[i]);
}

/**
 * @brief Copies one memory region onto another. Undefined behaviour in case of
 * overlap between the memory regions.
 * @param dst	Start of the destination region.
 * @param src	Start of the Source region.
 * @param n		Number of bytes to copy.
 * @return dst
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

/**
 * @brief Moves data from one memory region into another. In the case of overlap
 * the copy happens without destroying the information.
 * @param dst	Start of the destination region.
 * @param src	Start of the source region.
 * @param len	Number of bytes to copy.
 * @return dst
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	else if (dst == src)
		return (dst);
	else if (src < dst)
	{
		i = len;
		while (--i != __UINT64_MAX__)
			((t_byte *)dst)[i] = ((t_byte *)src)[i];
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}

/**
 * @brief Set each byte within a memory region to a specific value.
 *
 * @param b		Start of memory region.
 * @param c		Value of byte.
 * @param len	Number of bytes to set.
 * @return b
 */
void	*ft_memset(void *b, t_byte c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((t_byte *)b)[i] = c;
		i++;
	}
	return (b);
}
