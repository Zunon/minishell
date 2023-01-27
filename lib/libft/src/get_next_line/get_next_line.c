/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:43:32 by kalmheir          #+#    #+#             */
/*   Updated: 2022/07/30 18:08:53 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*get_next_line(int fd)
{
	int		i;
	int		rd;
	char	character;
	char	*buffer;

	i = 0;
	rd = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = malloc(10000);
	rd = read(fd, &character, 1);
	while (rd > 0)
	{
		rd = read(fd, &character, 1);
		buffer[i++] = character;
		if (character == '\n')
			break ;
	}
	if ((!buffer[i - 1] && !rd) || rd == -1)
	{
		free(buffer);
		return (0);
	}
	buffer[i] = '\0';
	return (buffer);
}
