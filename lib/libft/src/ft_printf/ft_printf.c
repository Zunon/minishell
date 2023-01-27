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
int	ft_printf(const char *str, ...)
{
	size_t	chars;
	va_list	args;

	chars = 0;
	va_start(args, str);
	iterator(str, &args, &chars);
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
void	put_charc(char c, size_t *count)
{
	(*count)++;
	write(STDOUT_FILENO, &c, 1);
}

/**
 * @brief Prints an unsigned long number to stdout using hexadecimal radix.
 *
 * @param num	Number to be printed to stdout.
 * @param count	Pointer to where the count is stored.
 */
void	put_longhex(unsigned long num, size_t *count)
{
	char	digit;

	if (num >= 16)
	{
		put_longhex(num / 16, count);
		num = num % 16;
	}
	digit = "0123456789abcdef"[num];
	put_charc(digit, count);
}

/**
 * @brief Chooses which printing function to be used based on the flag passed.
 *
 * @param c		Format specifier.
 * @param list	Argument list to fetch values from.
 * @param count	Pointer to where the count is stored.
 */
void	switcher(char c, va_list *list, size_t *count)
{
	if (c == 'c')
		put_charc(va_arg(*list, int), count);
	else if (c == 's')
		putstrc(va_arg(*list, char *), count);
	else if (c == 'p')
		put_pointerc(va_arg(*list, void *), count);
	else if (c == 'd' || c == 'i')
		put_nbrc(va_arg(*list, int), count);
	else if (c == 'u')
		put_unbrc(va_arg(*list, unsigned int), count);
	else if (c == 'x' || c == 'X')
		put_hex(va_arg(*list, unsigned int),
			(unsigned char)((c - 'X') / 32), count);
	else if (c == '%')
		put_charc('%', count);
}

/**
 * @brief Iterates through the formatted string, printing the string to stdout
 * and passing format specifiers to switcher().
 *
 * @param str	Formatted string passed to ft_printf().
 * @param list	Variadic argument list passed to ft_printf().
 * @param count	Pointer to where the count is stored.
 */
void	iterator(const char *str, va_list *list, size_t *count)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '%')
			put_charc(str[i], count);
		else
		{
			i++;
			if (str[i] == 0)
				break ;
			switcher(str[i], list, count);
		}
		i++;
	}
}
