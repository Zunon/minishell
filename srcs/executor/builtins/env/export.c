/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:27:24 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/27 19:15:41 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

t_dict	*combine_dictionary(t_dict *d1, t_dict *d2)
{
	t_dict	*d3;
	int		i;

	d3 = duplicate_dictionary(d1);
	i = 0;
	while (i < d2->capacity)
	{
		if (d2->table[i])
			insert_into_dict(&d3, d2->table[i]->key, d2->table[i]->value);
		i++;
	}
	return (d3);
}

/**
 * @brief				Print all environment variables in a sorted manner if
 * 						there are no arguments to export
 *
 * @return int			Status code of operation (discard if not needed)
 */
static int	export_no_args(void)
{
	t_dict	*merged;
	t_dict	*sorted;
	int		i;

	i = 0;
	merged = combine_dictionary(g_krsh.env_mngr, g_krsh.declared);
	sorted = sort_dictionary(merged, ft_strncmp);
	while (sorted->table[i])
	{
		if (sorted->table[i])
			ft_printf("declare -x %s", sorted->table[i]->key);
		if (sorted->table[i]->value)
			ft_printf("=\"%s\"\n", sorted->table[i]->value);
		else
			ft_printf("\n");
		i++;
	}
	destroy_dict(&sorted);
	destroy_dict(&merged);
	return (EXIT_SUCCESS);
}

static void	export_var(char *argument, int pos)
{
	if (argument)
	{
		if (!is_valid_identifier(argument))
		{
			fd_printf(STDERR_FILENO, "export: '%s': not a valid identifier\n",
				argument);
			g_krsh.status_code = ERROR_DURING_BUILTIN_EXEC;
			return ;
		}
		pos = find_pos(argument, '=');
		if (pos == -1)
		{
			if (!retrieve_from_dict(g_krsh.declared, argument))
				if (!retrieve_from_dict(g_krsh.env_mngr, argument))
					insert_into_dict(&g_krsh.declared, argument, NULL);
		}
		else
			add_to_env_mngr(argument, pos);
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

	pos = 0;
	i = 1;
	if (!cmd->argv[1])
		return (export_no_args());
	else
	{
		iterator = cmd->words->next;
		while (iterator)
		{
			export_var(iterator->content, pos);
			iterator = iterator->next;
			i++;
		}
	}
	return (g_krsh.status_code);
}
