/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:49:43 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/19 19:49:43 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief				Function to handle various signals in the program
 *
 * @param sig			Signal recieved by the program
 */
void	sig_handler(int sig)
{
	int	i;

	i = -1;
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(2, "  \n", 4);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_krsh.status_code = CONTROL_C_INTERRUPT;
	}
	if (sig == 4)
	{
		destroy_dict(g_krsh.env_mngr);
		while (g_krsh.envp[++i])
			free(g_krsh.envp[i]);
		free(g_krsh.envp);
		exit(EXIT_SUCCESS);
	}
}
