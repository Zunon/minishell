/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:20:39 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/22 02:56:13 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief 		Print current working directory of user
 *
 * @return int	status code of execution
 */
int	pwd(char **cmd)
{
	char	*path;

	if (cmd[1])
		return (EXIT_SUCCESS);
	path = NULL;
	path = getcwd(path, 0);
	if (!path)
	{
		perror("cd: error retrieving current directory: getcwd: ");
		return (EXIT_SUCCESS);
	}
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(path);
	return (EXIT_SUCCESS);
}
