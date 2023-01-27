/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:37:16 by kalmheir          #+#    #+#             */
/*   Updated: 2022/06/26 18:38:09 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/**
 * @brief Creates an array of vertices of a regular hexagon centered at a point.
 *
 * @param side		Length of a side of the hexagon.
 * @param center	Center of the hexagon.
 * @return Array of points that make up the corners/vertices of the hexagon.
 */
t_point	*make_hex_verts(int side, t_point center)
{
	double	cospi6;

	cospi6 = sqrt(3) / 2;
	return ((t_point [6]){
		(t_point){center.x, center.y - side},
		(t_point){center.x + (cospi6 * side), center.y - (side / 2)},
		(t_point){center.x + (cospi6 * side), center.y + (side / 2)},
		(t_point){center.x, center.y + side},
		(t_point){center.x - (cospi6 * side), center.y + (side / 2)},
		(t_point){center.x - (cospi6 * side), center.y - (side / 2)}
	});
}

/**
 * @brief Puts a regular hexagon onto the image.
 *
 * @param data	Image data struct.
 * @param side	Length of a side of the hexagon.
 * @param color	Color of the hexagon outline.
 */
void	put_hexagon(t_data *data, int side, t_color color)
{
	t_point	*vertices;
	t_point	center;
	t_line	*edges;
	int		i;

	center = (t_point){data->width / 2, data->height / 2};
	vertices = make_hex_verts(side, center);
	i = -1;
	edges = (t_line [6]){
		(t_line){vertices[0], vertices[1]},
		(t_line){vertices[1], vertices[2]},
		(t_line){vertices[3], vertices[2]},
		(t_line){vertices[4], vertices[3]},
		(t_line){vertices[5], vertices[4]},
		(t_line){vertices[5], vertices[0]}
	};
	i = 0;
	while (i < 6)
		put_line(data, &edges[i++], color);
}

/**
 * @brief Puts a vertical gradient at a specific portion of the image.
 *
 * @param data		Image data struct.
 * @param colors	The two colors that make up the gradient.
 * @param begin		Beginning of the gradient as a fraction of the image height.
 * @param end		End of the gradient as a fraction of the image height.
 */
void	put_grad_vertical(t_data *data, t_color *colors, double begin,
	double end)
{
	double	j;
	t_color	top_clr;
	t_color	bot_clr;

	top_clr = colors[0];
	bot_clr = colors[1];
	j = begin;
	while (j < end)
	{
		put_line(data, &(t_line){{0, j * data->height}, {data->width, j
			* data->height}}, mix_colors(top_clr, bot_clr, (j - begin)
				/ (end - begin)));
		j += (end - begin) / data->height;
	}
}

/**
 * @brief Puts a horizontal gradient at a specific portion of the image.
 *
 * @param data		Image data struct.
 * @param colors	The two colors that make up the gradient.
 * @param begin		Beginning of the gradient as a fraction of the image width.
 * @param end		End of the gradient as a fraction of the image width.
 */
void	put_grad_horizontal(t_data *data, t_color *colors, double begin,
	double end)
{
	double	j;
	t_color	top_clr;
	t_color	bot_clr;

	top_clr = colors[0];
	bot_clr = colors[1];
	j = begin;
	while (j < end)
	{
		put_line(data, &(t_line){{j * data->width, 0}, {j * data->width,
			data->height}}, mix_colors(top_clr, bot_clr, (j - begin)
				/ (end - begin)));
		j += (end - begin) / data->width;
	}
}
