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
int	ft_env(void)
{
	print_dict(g_krsh.env_mngr);
	return (EXIT_SUCCESS);
}

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

/**
 * @brief				Print all environment variables in a sorted manner if
 * 						there are no arguments to export
 *
 * @return int			Status code of operation (discard if not needed)
 */
static int	ft_export_no_args(void)
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

/**
 * @brief				Add new envrionment variable into the shell
 *
 * @param key			Variable name
 * @param value			Variable value
 * @return int			Status code of insertion
 */
int	ft_export(t_command *cmd)
{
	t_list	*iterator;
	int		i;
	int		pos;
	char	*key;
	char	*value;

	pos = 0;
	i = 1;
	if (!cmd->argv[1])
		return (ft_export_no_args());
	else
	{
		iterator = cmd->words->next;
		while (iterator)
		{
			export_string(iterator->content, pos, key, value);
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
int	ft_unset(char **argv)
{
	int	i;

	i = 1;
	if (!argv[1])
		return (EXIT_SUCCESS);
	while (argv[i])
	{
		remove_from_dict(g_krsh.env_mngr, argv[1]);
		i++;
	}
	update_env(g_krsh.env_mngr);
	return (EXIT_SUCCESS);
}
