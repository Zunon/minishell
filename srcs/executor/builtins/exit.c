/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:19:25 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/21 23:07:26 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	valid_exit_args(char *args)
{
	int i;

	i = 0;
	while (args[i])
	{
		if (!ft_isdigit(args[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}


static void	dup_stdout_and_exit(int status)
{
	if (g_krsh.num_of_cmds == 1)
	{
		dup2(g_krsh.stdout_old, STDOUT_FILENO);
		close(g_krsh.stdout_old);
	}
	exit_minishell(g_krsh.cmds, status);
}
/**
 * @brief		Exit from minishell safely
 *
 */
int	ft_exit(t_command *cmd)
{
	int	x;

	ft_printf("exit\n");
	if (!(cmd->argv[1]))
		dup_stdout_and_exit(g_krsh.status_code);
	if (cmd->argv[2])
	{
		fd_printf(STDERR_FILENO, "exit: too many arguments!\n");
		return (ERROR_DURING_BUILTIN_EXEC);
	}
	if (cmd->argv[1])
	{
		x = ft_atoi(cmd->argv[1]);
		if (valid_exit_args(cmd->argv[1]))
		{
			fd_printf(STDERR_FILENO, "exit: %s: numeric argument required\n",
				cmd->argv[1]);
			x = ERROR_NUMERIC_ARG_REQUIRED;
		}
		dup_stdout_and_exit(x);
	}
	return (ERROR_NUMERIC_ARG_REQUIRED);
}
