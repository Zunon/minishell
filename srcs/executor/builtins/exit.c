/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:19:25 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/19 19:19:25 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief		Exit from minishell safely
 *
 */
void	ft_exit(char **argv)
{
	int	x;

	if (!argv || !argv[1])
	{
		if (g_krsh.num_of_cmds == 1)
		{
			dup2(g_krsh.stdout_old, STDOUT_FILENO);
			close(g_krsh.stdout_old);
		}
		exit(0);
	}
	if (argv[1])
	{
		x = ft_atoi(argv[1]);
		if (g_krsh.num_of_cmds == 1)
		{
			dup2(g_krsh.stdout_old, STDOUT_FILENO);
			close(g_krsh.stdout_old);
		}
		exit(x & 0xff);
	}
	if (argv[2])
		ft_printf("exit: too many arguments!\n");
}