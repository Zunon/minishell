/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:20:41 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/22 02:55:15 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	update_env_pwds(void)
{
	t_pair	*oldpwd;
	t_pair	*pwd;
	char	*newpwd;

	newpwd = NULL;
	oldpwd = retrieve_from_dict(g_krsh.env_mngr, "OLDPWD");
	if (oldpwd)
	{
		pwd = retrieve_from_dict(g_krsh.env_mngr, "PWD");
		if (pwd)
			insert_into_dict(&g_krsh.env_mngr, "OLDPWD", pwd->value);
		newpwd = getcwd(newpwd, 0);
		if (!newpwd)
			perror("Error while gettign current working directory: ");
		insert_into_dict(&g_krsh.env_mngr, "PWD", newpwd);
		free(newpwd);
	}
}

/**
 * @brief 		Function to change from current working directory to another
 *
 * @param cmd	Command with arguments (incuding new path)
 * @return int	status code of execution
 */
int	cd(char **cmd)
{
	if (!cmd[1])
		return (EXIT_SUCCESS);
	if (chdir(cmd[1]) == -1)
	{
		perror(cmd[1]);
		if (g_krsh.num_of_cmds > 1)
			exit(1);
		return (ERROR_DURING_EXECUTION);
	}
	update_env_pwds();
	return (EXIT_SUCCESS);
}
