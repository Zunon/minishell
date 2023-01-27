/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:32:16 by kalmheir          #+#    #+#             */
/*   Updated: 2022/06/26 15:47:18 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/**
 * @brief Prints a formatted string to stdout the mimics the original printf()
 * function from libc (stdio.h)
 *
 * @param str	Input string, with formatting macros.
 * @param ...	Variadic variables to be printed out inside the string.
 * @return Total number of printed characters
 * @note Doesn't implement the buffer management of printf()
 * Handles the following conversions:
 *  %c - Character
 *  %s - String
 *  %p - Pointer (void * -> hex integer)
 *  %d and %i - Signed Integer
 *  %u - Unsigned Integer
 *  %x - Lowercase Hexadecimal Integer
 *  %X - Uppercase Hexadecimal Integer
 *  %% - Escaped % symbol
 */
int	fd_printf(int fd, const char *str, ...)
{
	size_t	chars;
	va_list	args;

	chars = 0;
	va_start(args, str);
	fd_iterator(fd, str, &args, &chars);
	va_end(args);
	return (chars);
}

/**
 * @brief Prints a character to stdout while also incrementing the ft_printf()
 * return value.
 *
 * @param c		Character to be printed.
 * @param count	Pointer to where the count is stored.
 */
void	fd_put_charc(int fd, char c, size_t *count)
{
	(*count)++;
	write(fd, &c, 1);
}

/**
 * @brief Prints an unsigned long number to stdout using hexadecimal radix.
 *
 * @param num	Number to be printed to stdout.
 * @param count	Pointer to where the count is stored.
 */
void	fd_put_longhex(int fd, unsigned long num, size_t *count)
{
	char	digit;

	if (num >= 16)
	{
		fd_put_longhex(fd, num / 16, count);
		num = num % 16;
	}
	digit = "0123456789abcdef"[num];
	fd_put_charc(fd, digit, count);
}

/**
 * @brief Chooses which printing function to be used based on the flag passed.
 *
 * @param c		Format specifier.
 * @param list	Argument list to fetch values from.
 * @param count	Pointer to where the count is stored.
 */
void	fd_switcher(int fd, char c, va_list *list, size_t *count)
{
	if (c == 'c')
		fd_put_charc(fd, va_arg(*list, int), count);
	else if (c == 's')
		fd_putstrc(fd, va_arg(*list, char *), count);
	else if (c == 'p')
		fd_put_pointerc(fd, va_arg(*list, void *), count);
	else if (c == 'd' || c == 'i')
		fd_put_nbrc(fd, va_arg(*list, int), count);
	else if (c == 'u')
		fd_put_unbrc(fd, va_arg(*list, unsigned int), count);
	else if (c == 'x' || c == 'X')
		fd_put_hex(fd, va_arg(*list, unsigned int),
			(unsigned char)((c - 'X') / 32), count);
	else if (c == '%')
		fd_put_charc(fd, '%', count);
}

/**
 * @brief Iterates through the formatted string, printing the string to stdout
 * and passing format specifiers to switcher().
 *
 * @param str	Formatted string passed to ft_printf().
 * @param list	Variadic argument list passed to ft_printf().
 * @param count	Pointer to where the count is stored.
 */
void	fd_iterator(int fd, const char *str, va_list *list, size_t *count)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '%')
			fd_put_charc(fd, str[i], count);
		else
		{
			i++;
			if (str[i] == 0)
				break ;
			fd_switcher(fd, str[i], list, count);
		}
		i++;
	}
}
