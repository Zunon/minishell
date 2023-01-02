/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:18:19 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/02 23:26:48 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int c1 ()
{
	char *cmd = ft_strdup("cat");
	char **av = malloc (sizeof (char *) * 3);

	av[0] = ft_strdup("cat");
	av[1] = ft_strdup("Makefile");
	av[2] = NULL;
	t_command *command = malloc(sizeof (t_command));
	command->fd_in = -1;
	command->fd_out = -1;
	command->redirects = malloc(sizeof (t_redirect));
	command->redirects->id = 0;
	command->redirects->direction = r_output;
	command->redirects->redirector = STDIN_FILENO;
	command->redirects->flags = O_CREAT | O_WRONLY;
	command->redirects->redirectee.word = ft_strdup("a");
	command->redirects->next = NULL;
	cmd_executor(command, cmd, av);
	return 0;
}
