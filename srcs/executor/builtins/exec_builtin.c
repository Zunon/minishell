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
	if (!cmd->argv || !cmd->argv[0])
		return (EXIT_SUCCESS);
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		return (cd(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (echo(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (pwd(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		ft_exit(cmd->argv);
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (env());
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		return (unset(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		return (export(cmd));
	return (EXIT_FAILURE);
}
