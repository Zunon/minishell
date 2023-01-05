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

/**
 * @brief		Add new envrionment variable into the shell
 *
 * @param key	Variable name
 * @param value	Variable value
 * @return int	Status code of insertion
 */
int ft_export(t_command *cmd)
{
	t_dict *dict;
	char **argv;
	t_word_list *iterator;
	int i;

	i = 1;
	argv = prepare_cmd_args(cmd->words);
	if (!argv[1]) /* export */
	{
		dict = sort_dictionary(zundra.env_mngr, ft_strncmp);
		print_dict(dict);
		destroy_dict(dict);
	}
	else
	{
		iterator = cmd->words->next;
		while (argv[i] && iterator)
		{
			if (iterator->curr_word_desc->assignment)
				insert_into_dict(&zundra.env_mngr, argv[0], argv[1]);
			iterator = iterator->next;
			i++;
		}

	}
	free(zundra.envp);
	zundra.envp = dict_to_string_arr(zundra.env_mngr);
	free(argv);
	return 0;
}

/**
 * @brief		Remove an environment variable
 *
 * @param key	Name of variable to delete
 * @return int	Status code of deletion (remove if not needed)
 */
int ft_unset(char **argv)
{
	int i;

	i = 0;
	if (argv[1])
	{
		remove_from_dict(zundra.env_mngr, argv[1]);
		free(zundra.env_mngr);
		zundra.envp = dict_to_string_arr(zundra.env_mngr);
	}
	return 0;
}