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
void ft_exit(char **argv)
{
	int x;

	if (argv[1])
	{
		x = ft_atoi(argv[1]);
		exit(x & 0xff);
	}
	exit(0);
}

/**
 * @brief 		Return status code of last executed command
 * 
 * @return int 	Status code of operation
 */
int status_code()
{
	ft_printf("%d", zundra.status_code);
	return (EXIT_SUCCESS);
}

/**
 * @brief		Builtin function handler for cd, echo, pwd, exit, env, export, unset
 *
 * @param cmd	Currently executimg command
 * @return int	Status code of child process after executing builtin OR ERROR_CODE 2
 * 				if not a builtin
 */
int exec_builtin(t_command *cmd, char **argv)
{
	if (!argv || !argv[0])
		return (EXIT_SUCCESS);
	if (ft_strncmp(argv[0], "cd", 2) == 0)
		return (ft_cd(argv));
	if (ft_strncmp(argv[0], "echo", 4) == 0 && argv[1] && ft_strncmp(argv[1], "$?", 2) == 0)
		return (status_code());
	if (ft_strncmp(argv[0], "echo", 4) == 0)
		return (ft_echo(argv));
	if (ft_strncmp(argv[0], "pwd", 3) == 0)
		return (ft_pwd());
	if (ft_strncmp(argv[0], "exit", 4) == 0)
		ft_exit(argv);
	if (ft_strncmp(argv[0], "env", 3) == 0)
		return (ft_env());
	if (ft_strncmp(argv[0], "unset", 5) == 0)
		return (ft_unset(argv));
	if (ft_strncmp(argv[0], "export", 6) == 0)
		return (ft_export(cmd));
	return (EXIT_FAILURE);
}