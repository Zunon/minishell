/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:27:26 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/19 19:27:26 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/**
 * @brief				Display all environment variables of the current shell
 *
 * @return int			status code of oepration (discard if not needed)
 */
int	env(void)
{
	print_dict(g_krsh.env_mngr);
	return (EXIT_SUCCESS);
}
