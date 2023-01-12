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
	if (cmd[1] && ft_strncmp(cmd[1], "-n", 2) == 0)
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
	return (EXIT_SUCCESS);
}

/**
 * @brief 		Function to change from current working directory to another
 *
 * @param cmd	Command with arguments (incuding new path)
 * @return int	status code of execution
 */
int ft_cd(char **cmd)
{
	t_pair *pair;
	/* Error Handling */
	if (!cmd[1])
		return (EXIT_SUCCESS);
	if (chdir(cmd[1]) == -1)
	{
		perror(cmd[1]);
		if (zundra.num_of_cmds > 1)
			exit(1);
		return (ERROR_DURING_EXECUTION);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief 		Print current working directory of user
 *
 * @return int	status code of execution
 */
int ft_pwd(char **cmd)
{
	char *path;

	if (cmd[1])
		return (EXIT_SUCCESS);
	path = getcwd(path, 1025);
	if (!path)
	{
		perror("Error while getting current working directory: ");
		return (ERROR_DURING_EXECUTION);
	}
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	if (path)
		free(path);
	return (EXIT_SUCCESS);
}