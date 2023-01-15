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

#include "../inc/minishell.h"


/**
 * @brief				Display all environment variables of the current shell
 *
 * @return int			status code of oepration (discard if not needed)
 */
int ft_env()
{
	print_dict(zundra.env_mngr);
	return (EXIT_SUCCESS);
}


/**
 * @brief				Update the environment variable manager dictionary after any
 * 						exports and/or unsets
 *
 * @param env_manager	Envrionment manager dictionary to update
 */
static void update_env(t_dict *env_manager)
{
	int i;
	char **strs;

	i = -1;
	if (!env_manager)
		return ;
	while (zundra.envp[++i])
		free(zundra.envp[i]);
	free(zundra.envp);
	strs = dict_to_string_arr(env_manager);
	zundra.envp = strs;
}

/**
 * @brief				Print all envrioment variables in a sorted manner if there
 * 						are no arguments to export
 *
 * @return int			Status code of operation (discard if not needed)
 */
static int ft_export_no_args()
{
	t_dict *dict;
	int i;

	i = 0;
	dict = sort_dictionary(zundra.env_mngr, ft_strncmp);
	while (dict->table[i])
	{
		if (dict->table[i])
			ft_printf("declare -x %s=\"%s\"\n", dict->table[i]->key, dict->table[i]->value);
		i++;
	}
	destroy_dict(dict);
	return (EXIT_SUCCESS);
}

/**
 * @brief				Add new envrionment variable into the shell
 *
 * @param key			Variable name
 * @param value			Variable value
 * @return int			Status code of insertion
 */
int ft_export(t_command *cmd)
{
	t_list *iterator;
	int i;
	int pos;
	char *key;
	char *value;

	pos = 0;
	i = 1;
	if (!cmd->argv[1]) /* export */
		return ft_export_no_args();
	else
	{
		iterator = cmd->words->next;
		while (iterator)
		{
			if (iterator->content)
			{
				pos = find_pos(iterator->content, '=');
				if (pos == -1 )
					insert_into_dict(&zundra.env_mngr, iterator->content, "");
				else
				{
					key = ft_substr(iterator->content, 0, pos);
					value = ft_substr(iterator->content, pos + 1, -1);
					insert_into_dict(&zundra.env_mngr, key, value);
					free(key);
					if (value)
						free(value);
				}
				update_env(zundra.env_mngr);
			}
			iterator = iterator->next;
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief				Remove an environment variable
 *
 * @param key			Name of variable to delete
 * @return int			Status code of deletion (remove if not needed)
 */
int ft_unset(char **argv)
{
	int i;

	i = 1;
	if (!argv[1])
		return (EXIT_SUCCESS);
	while (argv[i])
	{
		remove_from_dict(zundra.env_mngr, argv[1]);
		i++;
	}
	update_env(zundra.env_mngr);
	return (EXIT_SUCCESS);
}