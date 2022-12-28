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

int ft_env()
{
	int i;

	i = 0;
	while (zundra.envp[i])
	{
		write(1, zundra.envp[i], ft_strlen(zundra.envp[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

int ft_exit()
{
	exit(42);
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
	return 2;
}