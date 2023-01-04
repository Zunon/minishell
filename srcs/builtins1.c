/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:37:31 by rriyas            #+#    #+#             */
/*   Updated: 2022/10/23 17:44:29 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief		Execute echo command wih option -n for no trailing newline
 *
 * @param cmd	command to execute with parameters
 * @return int	status code of execution
 */
int	ft_echo(char **cmd)
{
	int i;
	int nl;

	nl = 1;
	i = 0;
	if (cmd[1] && ft_strncmp(cmd[1], "-n\0", 3) == 0)
	{
		nl = 0;
		i++;
	}
	while (cmd[++i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i+1])
			write(1, " ", 1);
	}
	if (nl == 1)
		write(1, "\n", 1);
	return (0);
}

/**
 * @brief 		Function to change from current working directory to another
 *
 * @param cmd	Command with arguments (incuding new path)
 * @return int	status code of execution
 */
int ft_cd(char **cmd)
{
	/* Error Handling */
	return (chdir(cmd[1]));
}

/**
 * @brief 		Print current working directory of user
 *
 * @return int	status code of execution
 */
int ft_pwd()
{
	char *path;

	path = malloc(1024 * sizeof(char));
	getcwd(path, 1024);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(path);
	return 0;
}