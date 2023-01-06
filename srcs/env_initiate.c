/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 11:51:12 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/05 18:37:26 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


static void update_shlvl(t_dict *env_manager)
{
	t_pair *shlvl;
	char *temp;

	shlvl = retrieve_from_dict(env_manager, "SHLVL");
	if (!shlvl)
	{
		insert_into_dict(&env_manager, "SHLVL", "1");
		return ;
	}
	temp = shlvl->value;
	shlvl->value = ft_itoa(ft_atoi(temp) + 1);
	free(temp);
}

static int find_pos(char *s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_dict *generate_env_manager(char **envp)
{
	t_dict *env_manager;
	int i;
	char *key;
	char *value;
	int pos;

	i = 0;
	env_manager = create_dict(50);
	while (envp[i])
	{
		pos = find_pos(envp[i], '=');
		if (pos != -1)
		{
			key = ft_substr(envp[i], 0, pos);
			value = ft_substr(envp[i], pos + 1, -1);
			insert_into_dict(&env_manager, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	update_shlvl(env_manager);	
	return (env_manager);
}

/**
 * @brief		Display all environment variables of the current shell
 *
 * @return int	status code of oepration (discard if not needed)
 */
int ft_env()
{
	print_dict(zundra.env_mngr);
	return (0);
}
