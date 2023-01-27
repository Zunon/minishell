/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:35:27 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/27 16:43:30 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief			Function to execute a simple command
 *
 * @param cmd		Command struct to execute
 * @param c			command as a char *
 * @param av		command and its parameters for use by execve
 * @return int		Status code of child process after execution
 */
int	exec_simple_cmd(t_command *cmd)
{
	pid_t	pid;

	if (exec_builtin_parent(cmd) != ERROR_COMMAND_NOT_FOUND)
		return (EXIT_SUCCESS);
	pid = fork();
	if (pid == -1)
	{
		ft_printf("Error while forking\n");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (perform_io_redirections(cmd) == EXIT_FAILURE)
			exit_minishell(g_krsh.cmds, EXIT_FAILURE);
		if (cmd->argv)
			ext_if_cmd_not_found(cmd);
		exit_minishell(g_krsh.cmds, g_krsh.status_code);
	}
	else
		signal(SIGINT, SIG_IGN);
	g_krsh.last_child_pid = pid;
	return (EXIT_SUCCESS);
}
