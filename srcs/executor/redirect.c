/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 07:01:24 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/22 07:02:04 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief			Function to open necessary files and perform all
 * 					redirections from left->right. If there are pipes, then the
 * 					necessary piping is handled as well. Handles input, heredoc,
 * 					output, output append
 *
 * @param cmd		Currently executing command
 * @return int		Status code (discard if not needed)
 */
int	perform_io_redirections(t_command *cmd)
{
	t_redirect	*iterator;
	int			status;

	status = EXIT_SUCCESS;
	iterator = cmd->redirects;
	if (piper(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (iterator && status != EXIT_FAILURE)
	{
		if (iterator->direction == HERE_DOC)
			status = redirect_heredoc(iterator);
		else if (iterator->direction == INPUT)
			status = redirect_input(cmd, iterator);
		else if (iterator->direction == OUTPUT
			|| iterator->direction == OUTPUT_APPEND)
			status = redirect_output(cmd, iterator);
		iterator = iterator->next;
	}
	return (status);
}
