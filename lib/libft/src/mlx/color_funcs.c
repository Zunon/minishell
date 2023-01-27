/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:25:18 by kalmheir          #+#    #+#             */
/*   Updated: 2022/06/26 18:24:26 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/**
 * @brief Get the integer representation of a color in the form of 0xAARRGGBB.
 *
 * @param color	Color to convert to an integer.
 * @return Integer representation of color.
 */
int	get_color(t_color color)
{
	return (color.blue + (color.green << 8) + (color.red << 16)
		+ (color.alpha << 24));
}

/**
 * @brief Create a color from the integer representation of that color.
 *
 * @param color	Color integer to be transformed to a color struct
 * @return Color struct representation of color.
 */
t_color	make_color(int color)
{
	return ((t_color){color >> 24, color >> 16, color >> 8, color});
}

/**
 * @brief Mix two colors in a certain distance between them.
 *
 * @param from		Starting color to mix from.
 * @param to		Destination color if proportion is 1.
 * @param amount	Distance between two colors, 0 being from and 1 being the to
 * color.
 * @return Intermediate color.
 */
t_color	mix_colors(t_color from, t_color to, double amount)
{
	return ((t_color){
		(to.alpha - from.alpha) * amount + from.alpha,
		(to.red - from.red) * amount + from.red,
		(to.green - from.green) * amount + from.green,
		(to.blue - from.blue) * amount + from.blue
	});
}

/**
 * @brief Shades a color a certain distance to black.
 * Equivalent to mix_colors(color, (t_color){0,0,0,0}, amount).
 * @param color		Color to be shaded.
 * @param amount	Distance towards black to shade, 0, being no change, 1 being
 * pitch black.
 * @return Shaded color.
 */
t_color	add_shade(t_color color, double amount)
{
	t_color	black;

	black = (t_color){0, 0, 0, 0};
	return (mix_colors(color, black, amount));
}

/**
 * @brief Inverts the given color.
 *
 * @param color	Color to be inverted.
 * @return Inverted color.
 */
t_color	get_opposite(t_color color)
{
	return ((t_color){
		0xFF - color.alpha,
		0xFF - color.red,
		0xFF - color.green,
		0xFF - color.blue
	});
}
