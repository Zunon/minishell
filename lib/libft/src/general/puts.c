/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:38:48 by kalmheir          #+#    #+#             */
/*   Updated: 2022/06/26 17:23:05 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/**
 * @brief Prints the given character to the given file descriptor.
 *
 * @param c		Character to be printed.
 * @param fd	File descriptor to be printed into.
 */
void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

/**
 * @brief Prints the given string to the given file descriptor, appending a new
 * line afterwards
 * @param s		String to be printed.
 * @param fd	File descriptor to be printed into.
 */
void	ft_putendl_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\n", fd);
}

/**
 * @brief Prints the given number to the given file descriptor.
 *
 * @param n		Number to be printed.
 * @param fd	File descriptor to be printed into.
 */
void	ft_putnbr_fd(int n, int fd)
{
	char	digit;

	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		n = n % 10;
	}
	digit = n + '0';
	write(fd, &digit, 1);
}

/**
 * @brief Prints the given string to the given file descriptor.
 *
 * @param s		String to be printed.
 * @param fd	File descriptor to be printed into.
 */
void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
}
