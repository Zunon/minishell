/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 11:51:12 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/02 18:14:39 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_env()
{
	print_ht(zundra.env_mngr);
	return (0);
}

int ft_export(char *key, char *value)
{
	insert_into_ht(&zundra.env_mngr, key, value);
	return 0;
}

int ft_unset(char *key)
{
	remove_from_ht(zundra.env_mngr, key);
	return 0;
}

