/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:39:38 by rriyas            #+#    #+#             */
/*   Updated: 2022/10/23 17:45:58 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief		Exit from minishell safely
 *
 */
void ft_exit()
{
	exit(0);
}

/**
 * @brief		Return status code of last executed command
 *
 * @return int	status code
 */
int status_code()
{
	printf("%d\n", zundra.status_code);
	return 0;
}

/**
 * @brief		Builtin function handler for cd, echo, pwd, exit, env, export, unset
 *
 * @param cmd	Currently executimg command
 * @return int	Status code of child process after executing builtin OR ERROR_CODE 2
 * 				if not a builtin
 */
int exec_builtin(char **cmd)
{
	if (ft_strncmp(cmd[0], "cd", 2) == 0)
		return ft_cd(cmd);
	if (ft_strncmp(cmd[0], "echo", 4) == 0 && cmd[1] && ft_strncmp(cmd[1], "$?", 2) == 0)
		return status_code();
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		return ft_echo(cmd);
	if (!cmd[1] && ft_strncmp(cmd[0], "pwd", 3) == 0)
		return ft_pwd();
	if (!cmd[1] && ft_strncmp(cmd[0], "exit", 4) == 0)
		ft_exit();
	if (!cmd[1] && ft_strncmp(cmd[0], "env", 3) == 0)
		return ft_env();
	if (!cmd[1] && ft_strncmp(cmd[0], "export", 6) == 0)
		return ft_export(cmd);
	if (!cmd[1] && ft_strncmp(cmd[0], "unset", 5) == 0)
		return ft_unset(cmd);
	return 2;
}