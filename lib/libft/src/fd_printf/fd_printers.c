/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:33:34 by kalmheir          #+#    #+#             */
/*   Updated: 2022/06/26 15:47:10 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/**
 * @brief Prints a string to stdout while keeping count.
 * Prints a '(null)' if str is a null pointer.
 * @param str	String to be printed out to stdout.
 * @param count	Pointer to where count is stored
 */
void	fd_putstrc(int fd, const char *str, size_t *count)
{
	int	i;

	i = 0;
	if (str == 0)
	{
		fd_putstrc(fd, "(null)", count);
		return ;
	}
	while (str[i])
		fd_put_charc(fd, str[i++], count);
}

/**
 * @brief Prints out a pointer onto stdout as a hexadecimal number starting with
 * '0x'.
 *
 * @param pointer	Pointer to be printed out to stdout.
 * @param count		Pointer to where count is stored.
 */
void	fd_put_pointerc(int fd, void *pointer, size_t *count)
{
	(*count) += 2;
	write(fd, "0x", 2);
	fd_put_longhex(fd, (unsigned long)pointer, count);
}

/**
 * @brief Prints out a number onto stdout as a decimal number.
 *
 * @param num	Number to be printed out to stdout.
 * @param count	Pointer to where count is stored.
 */
void	fd_put_nbrc(int fd, int num, size_t *count)
{
	char	digit;

	if (num == -2147483648)
	{
		fd_putstrc(fd, "-2147483648", count);
		return ;
	}
	else if (num < 0)
	{
		fd_put_charc(fd, '-', count);
		num = -num;
	}
	if (num >= 10)
	{
		fd_put_nbrc(fd, num / 10, count);
		num = num % 10;
	}
	digit = num + '0';
	fd_put_charc(fd, digit, count);
}

/**
 * @brief Prints out a number onto stdout as an unsigned decimal number.
 *
 * @param num	Number to be printed out to stdout.
 * @param count	Pointer to where count is stored.
 */
void	fd_put_unbrc(int fd, unsigned int num, size_t *count)
{
	char	digit;

	if (num >= 10)
	{
		fd_put_unbrc(fd, num / 10, count);
		num = num % 10;
	}
	digit = num + '0';
	fd_put_charc(fd, digit, count);
}

/**
 * @brief Prints out a number onto stdout as a hexadecimal number.
 *
 * @param num		Number to be printed out to stdout.
 * @param isLower	Whether or not to print it in lowercase or uppercase form.
 * @param count		Ponter to where count is stored
 */
void	fd_put_hex(int fd, unsigned int num, t_bool isLower, size_t *count)
{
	char	digit;

	if (num >= 16)
	{
		fd_put_hex(fd, num / 16, isLower, count);
		num = num % 16;
	}
	if (isLower)
		digit = "0123456789abcdef"[num];
	else
		digit = "0123456789ABCDEF"[num];
	fd_put_charc(fd, digit, count);
}
