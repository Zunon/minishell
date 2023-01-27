/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_bools1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:45:10 by kalmheir          #+#    #+#             */
/*   Updated: 2022/06/26 18:47:11 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/**
 * @brief Return whether or not character is whitespace.
 *
 * @param c	Character to be checked.
 * @return Boolean value.
 */
t_bool	ft_iswhitespace(char c)
{
	return ((c >= 0x09 && c <= 0x0d) || c == 0x20);
}
