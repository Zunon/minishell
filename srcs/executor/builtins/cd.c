/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:20:41 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/20 23:44:15 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief 		Function to change from current working directory to another
 *
 * @param cmd	Command with arguments (incuding new path)
 * @return int	status code of execution
 */
int	cd(char **cmd)
{
	t_pair	*oldpwd;
	t_pair	*pwd;
	char	*old;
	char	*newpwd;

	if (!cmd[1])
		return (EXIT_SUCCESS);
	if (chdir(cmd[1]) == -1)
	{
		perror(cmd[1]);
		if (g_krsh.num_of_cmds > 1)
			exit(1);
		return (ERROR_DURING_EXECUTION);
	}
	oldpwd = retrieve_from_dict(g_krsh.env_mngr, "OLDPWD");
	if (oldpwd)
	{
		pwd = retrieve_from_dict(g_krsh.env_mngr, "PWD");
		if (pwd)
			insert_into_dict(&g_krsh.env_mngr, "OLDPWD", pwd->value);
		newpwd = malloc(sizeof(char) * 1025);
		newpwd = getcwd(newpwd, -1);
		insert_into_dict(&g_krsh.env_mngr, "PWD", newpwd);
		free(newpwd);
	}
	return (EXIT_SUCCESS);
}
