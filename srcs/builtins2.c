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

int ft_exit()
{
	exit(0);
}

int status_code()
{
	printf("%d\n", zundra.status_code);
	return 0;
}

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
		return ft_exit();
	if (!cmd[1] && ft_strncmp(cmd[0], "env", 3) == 0)
		return ft_env();
	if (!cmd[1] && ft_strncmp(cmd[0], "export", 6) == 0)
		return ft_export(cmd[1], cmd[2]);
	if (!cmd[1] && ft_strncmp(cmd[0], "unset", 5) == 0)
		return ft_unset(cmd[1]);
	return 2;
}