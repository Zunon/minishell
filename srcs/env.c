/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 11:51:12 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/04 14:48:50 by rriyas           ###   ########.fr       */
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
	print_ht(zundra.env_mngr);
	return (0);
}

/**
 * @brief		Add new envrionment variable into the shell
 *
 * @param key	Variable name
 * @param value	Variable value
 * @return int	Status code of insertion
 */
int ft_export(char *key, char *value)
{
	insert_into_ht(&zundra.env_mngr, key, value);
	return 0;
}

/**
 * @brief		Remove an environment variable
 *
 * @param key	Name of variable to delete
 * @return int	Status code of deletion (remove if not needed)
 */
int ft_unset(char *key)
{
	remove_from_ht(zundra.env_mngr, key);
	return 0;
}