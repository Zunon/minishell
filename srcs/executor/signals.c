/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:49:43 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/20 22:39:36 by rriyas           ###   ########.fr       */
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
		write(STDERR_FILENO, "  \n", 4);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_krsh.status_code = CONTROL_C_INTERRUPT;
	}
}

int	get_signal_code(int code)
{
	if (code == SIGINT)
		return (130);
	return (131);
}

void	wait_section(int *status)
{
	if (waitpid(g_krsh.last_child_pid, status, 0) == -1)
		return ;
	if (WIFSIGNALED((*status)))
		g_krsh.status_code = get_signal_code(WTERMSIG((*status)));
	else
		g_krsh.status_code = WEXITSTATUS((*status));
	while (waitpid(-1, status, 0) > -1)
		;
}

t_bool	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (FALSE);
	if (ft_isdigit(str[0]))
		return (FALSE);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
