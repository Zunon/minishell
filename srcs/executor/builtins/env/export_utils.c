/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 07:06:16 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/22 07:09:01 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

void	set_in_dict(const char *argument, int pos)
{
	char	*key;
	char	*value;

	key = ft_substr(argument, 0, pos);
	value = ft_substr(argument, pos + 1, -1);
	if (retrieve_from_dict(g_krsh.declared, key))
		remove_from_dict(g_krsh.declared, key);
	insert_into_dict(&g_krsh.env_mngr, key, value);
	free(key);
	if (value)
		free(value);
	update_env(g_krsh.env_mngr);
}
