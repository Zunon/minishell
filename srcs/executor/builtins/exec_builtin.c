/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:39:34 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/19 19:39:34 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief		Builtin function handler for cd, echo, pwd, exit, env, export,
 * 				and unset
 *
 * @param cmd	Currently executing command
 * @return int	Status code of child process after executing builtin OR
 * 				ERROR_CODE 2 if not a builtin
 */
int	exec_builtin(t_command *cmd)
{
	int status;

	status = EXIT_FAILURE;
	if (!cmd->argv || !cmd->argv[0])
		return (EXIT_SUCCESS);
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		status = cd(cmd->argv);
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		status = echo(cmd->argv);
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		status = pwd(cmd->argv);
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		ft_exit(cmd->argv);
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		status = env();
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		status = unset(cmd->argv);
	if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		status = export(cmd);
	if (g_krsh.num_of_cmds != 1 && status == EXIT_SUCCESS)
		exit_minishell(cmd, status);
	return (status);
}
