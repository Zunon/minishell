/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_bools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:06:31 by kalmheir          #+#    #+#             */
/*   Updated: 2022/06/26 15:50:45 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/**
 * @brief Return whether or not character is alphanumeric.
 *
 * @param c	Character to be checked.
 * @return Boolean value.
 */
t_bool	ft_isalnum(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

/**
 * @brief Return whether or not character is alphabetical.
 *
 * @param c	Character to be checked.
 * @return Boolean value.
 */
t_bool	ft_isalpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

/**
 * @brief Return whether or not character is part of the ASCII standard. In
 * Unicode's UTF-8 encoding this corresponds to a leading byte that has no
 * trailing bytes.
 * @param c	Character to be checked.
 * @return Boolean value.
 */
t_bool	ft_isascii(char c)
{
	return (c >= 0);
}

/**
 * @brief Return whether or not character is a numerical digit.
 *
 * @param c	Character to be checked.
 * @return Boolean value.
 */
t_bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

/**
 * @brief Return whether or not character is printable. This only applies to
 * characters within the ASCII standard, any input outside of that scope causes
 * undefined behaviour.
 * @param c	Character to be checked.
 * @return Boolean value.
 */
t_bool	ft_isprint(char c)
{
	return (c >= ' ' && c <= '~');
}
