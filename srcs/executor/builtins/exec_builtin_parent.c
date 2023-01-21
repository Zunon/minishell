/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_parent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:39:38 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/21 22:36:21 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_bool	is_builtin(t_command *cmd)
{
	if (!cmd->argv || !cmd->argv[0])
		return (FALSE);
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		return (TRUE);
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (TRUE);
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (TRUE);
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		return (TRUE);
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (TRUE);
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		return (TRUE);
	if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		return (TRUE);
	return (FALSE);
}

int	exec_builtin_parent(t_command *cmd)
{
	if (g_krsh.num_of_cmds == 1 && is_builtin(cmd))
	{
		g_krsh.stdout_old = dup(STDOUT_FILENO);
		g_krsh.stdin_old = dup(STDIN_FILENO);
		if (perform_io_redirections(cmd) == EXIT_FAILURE)
		{
			dup2(g_krsh.stdout_old, STDOUT_FILENO);
			close(g_krsh.stdout_old);
			dup2(g_krsh.stdin_old, STDIN_FILENO);
			close(g_krsh.stdin_old);
			return (EXIT_FAILURE);
		}
		if (exec_builtin(cmd) == EXIT_SUCCESS)
		{
			dup2(g_krsh.stdout_old, STDOUT_FILENO);
			close(g_krsh.stdout_old);
			dup2(g_krsh.stdin_old, STDIN_FILENO);
			close(g_krsh.stdin_old);
			g_krsh.status_code = EXIT_SUCCESS;
			return (EXIT_SUCCESS);
		}
		dup2(g_krsh.stdout_old, STDOUT_FILENO);
		close(g_krsh.stdout_old);
		dup2(g_krsh.stdin_old, STDIN_FILENO);
		close(g_krsh.stdin_old);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
