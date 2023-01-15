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

	if (!argv || !argv[1])
		exit(0);
	if (argv[1])
	{
		x = ft_atoi(argv[1]);
		exit(x & 0xff);
	}
	if (argv[2])
		ft_printf("exit: too many arguments!\n");
}

/**
 * @brief 		Return status code of last executed command
 *
 * @return int 	Status code of operation
 */
int status_code()
{
	ft_printf("%d\n", g_krsh.status_code);
	return (EXIT_SUCCESS);
}

/**
 * @brief		Builtin function handler for cd, echo, pwd, exit, env, export, unset
 *
 * @param cmd	Currently executimg command
 * @return int	Status code of child process after executing builtin OR ERROR_CODE 2
 * 				if not a builtin
 */
int exec_builtin(t_command *cmd)
{
	if (!cmd->argv || !cmd->argv[0])
		return (EXIT_SUCCESS);
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		return (ft_cd(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (ft_echo(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (ft_pwd(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		ft_exit(cmd->argv);
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (ft_env());
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		return (ft_unset(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		return (ft_export(cmd));
	return (EXIT_FAILURE);
}
