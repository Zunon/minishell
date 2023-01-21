/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:27:22 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/20 13:54:39 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/**
 * @brief				Remove an environment variable
 *
 * @param key			Name of variable to delete
 * @return int			Status code of deletion (remove if not needed)
 */
int	unset(char **argv)
{
	int	i;

	i = 1;
	if (!argv[1])
		return (EXIT_SUCCESS);
	while (argv[i])
	{
		remove_from_dict(g_krsh.env_mngr, argv[i]);
		remove_from_dict(g_krsh.declared, argv[i]);
		i++;
	}
	update_env(g_krsh.env_mngr);
	return (EXIT_SUCCESS);
}