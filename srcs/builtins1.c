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

static int	check_valid_option(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '-')
			{
				j++;
				while (cmd[i][j] && cmd[i][j] == 'n')
					j++;
				if (cmd[i][j])
					return (-1);
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief		Execute echo command wih option -n for no trailing newline
 *
 * @param cmd	command to execute with parameters
 * @return int	status code of execution
 */
int	ft_echo(char **cmd)
{
	int	i;
	int	nl;

	nl = 1;
	i = 0;
	if (cmd[1] && ft_strncmp(cmd[1], "-n", 3) == 0)
	{
		nl = 0;
		i++;
	}
	while (cmd[++i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
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
int	ft_cd(char **cmd)
{
	t_pair	*pair;

	if (!cmd[1])
		return (EXIT_SUCCESS);
	if (chdir(cmd[1]) == -1)
	{
		perror(cmd[1]);
		if (g_krsh.num_of_cmds > 1)
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
int	ft_pwd(char **cmd)
{
	char	*path;

	if (cmd[1])
		return (EXIT_SUCCESS);
	path = malloc(1025 * sizeof(char));
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
