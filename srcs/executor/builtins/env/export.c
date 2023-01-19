/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:27:24 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/19 19:27:24 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/**
 * @brief				Print all environment variables in a sorted manner if
 * 						there are no arguments to export
 *
 * @return int			Status code of operation (discard if not needed)
 */
static int	export_no_args(void)
{
	t_dict	*dict;
	int		i;

	i = 0;
	dict = sort_dictionary(g_krsh.env_mngr, ft_strncmp);
	while (dict->table[i])
	{
		if (dict->table[i])
			ft_printf("declare -x %s=\"%s\"\n", dict->table[i]->key,
				dict->table[i]->value);
		i++;
	}
	destroy_dict(dict);
	return (EXIT_SUCCESS);
}

static void	export_var(char *argument, int pos, char *key, char *value)
{
	if (argument)
	{
		pos = find_pos(argument, '=');
		if (pos == -1)
			insert_into_dict(&g_krsh.env_mngr, argument, "");
		else
		{
			key = ft_substr(argument, 0, pos);
			value = ft_substr(argument, pos + 1, -1);
			insert_into_dict(&g_krsh.env_mngr, key, value);
			free(key);
			if (value)
				free(value);
		}
		update_env(g_krsh.env_mngr);
	}
}

/**
 * @brief				Add new envrionment variable into the shell
 *
 * @param key			Variable name
 * @param value			Variable value
 * @return int			Status code of insertion
 */
int	export(t_command *cmd)
{
	t_list	*iterator;
	int		i;
	int		pos;
	char	*key;
	char	*value;

	pos = 0;
	i = 1;
	if (!cmd->argv[1])
		return (export_no_args());
	else
	{
		iterator = cmd->words->next;
		while (iterator)
		{
			export_var(iterator->content, pos, key, value);
			iterator = iterator->next;
			i++;
		}
	}
	return (EXIT_SUCCESS);
}