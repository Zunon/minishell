/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:20:39 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/19 19:20:39 by rriyas           ###   ########.fr       */
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