/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:20:43 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/19 19:20:43 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"


static int	check_valid_option(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '-')
			{
				j++;
				while (cmd[i][j] && cmd[i][j] == 'n')
					j++;
				if (cmd[i][j])
					return (-1);
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief		Execute echo command wih option -n for no trailing newline
 *
 * @param cmd	command to execute with parameters
 * @return int	status code of execution
 */
int	echo(char **cmd)
{
	int	i;
	int	nl;

	nl = 1;
	i = 0;
	if (cmd[1] && ft_strncmp(cmd[1], "-n", 3) == 0)
	{
		nl = 0;
		i++;
	}
	while (cmd[++i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
	}
	if (nl == 1)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
