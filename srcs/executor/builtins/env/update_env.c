/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:56:25 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/06 20:56:25 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/**
 * @brief				Update the environment variable manager dictionary after
 * 						any exports and/or unsets
 *
 * @param env_manager	Envrionment manager dictionary to update
 */
void	update_env(t_dict *env_manager)
{
	int		i;
	char	**strs;

	i = -1;
	if (!env_manager)
		return ;
	while (g_krsh.envp[++i])
		free(g_krsh.envp[i]);
	free(g_krsh.envp);
	strs = dict_to_string_arr(env_manager);
	g_krsh.envp = strs;
}
