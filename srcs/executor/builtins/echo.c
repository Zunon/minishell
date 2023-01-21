/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:20:43 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/20 18:29:43 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_bool valid_n_option(char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/**
 * @brief		Execute echo command wih option -n for no trailing newline
 *
 * @param argv	command to execute with parameters
 * @return int	status code of execution
 */
int	echo(char **argv)
{
	int	i;
	t_bool	nl;

	nl = TRUE;
	i = 1;
	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
	{
		while (argv[i] && !ft_strncmp(argv[i], "-n", 2))
		{
			if (valid_n_option(argv[i]))
			{
				if (nl == TRUE)
					nl = FALSE;
			}
			else
				break ;
			i++;
		}
	}
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl == 1)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
