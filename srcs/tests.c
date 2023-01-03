/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:18:19 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/03 11:07:01 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int c1 (/* cat Makefile > a >> b >> c*/)
{
	char *cmd = ft_strdup("cat");
	char **av = malloc (sizeof (char *) * 3);

	av[0] = ft_strdup("cat");
	av[1] = ft_strdup("Makefile");
	av[2] = NULL;


	t_command *command = malloc(sizeof (t_command));
	command->fd_in = -1;
	command->fd_out = -1;
	command->stdout_old = dup(STDOUT_FILENO);
	command->stdin_old = dup(STDIN_FILENO);

	command->redirects = malloc(sizeof (t_redirect));
	command->redirects->id = 0;
	command->redirects->direction = r_output;
	command->redirects->redirector = STDIN_FILENO;
	command->redirects->flags = O_CREAT | O_WRONLY | O_TRUNC;
	command->redirects->redirectee.word = ft_strdup("a");

	command->redirects->next = malloc(sizeof (t_redirect));
	command->redirects->next->id = 0;
	command->redirects->next->direction = r_output;
	command->redirects->next->redirector = STDIN_FILENO;
	command->redirects->next->flags = O_CREAT | O_WRONLY | O_APPEND;
	command->redirects->next->redirectee.word = ft_strdup("b");

	command->redirects->next->next = malloc(sizeof(t_redirect));
	command->redirects->next->next->id = 0;
	command->redirects->next->next->direction = r_output;
	command->redirects->next->next->redirector = STDIN_FILENO;
	command->redirects->next->next->flags = O_CREAT | O_WRONLY | O_APPEND;
	command->redirects->next->next->redirectee.word = ft_strdup("c");
	command->redirects->next->next->next = NULL;

	undo_redirections(command);
	return 0;
}

int c2(/* <d grep a > e >> app */)
{
	char *cmd = ft_strdup("grep");
	char **av = malloc(sizeof(char *) * 3);

	av[0] = ft_strdup("grep");
	av[1] = ft_strdup("a");
	av[2] = NULL;

	t_command *command = malloc(sizeof(t_command));
	command->fd_in = -1;
	command->fd_out = -1;
	command->stdout_old = dup(STDOUT_FILENO);
	command->stdin_old = dup(STDIN_FILENO);

	command->redirects = malloc(sizeof(t_redirect));
	command->redirects->id = 0;
	command->redirects->direction = r_input;
	command->redirects->redirector = STDIN_FILENO;
	command->redirects->flags = O_CREAT | O_RDONLY;
	command->redirects->redirectee.word = ft_strdup("d");

	command->redirects->next = malloc(sizeof(t_redirect));
	command->redirects->next->id = 1;
	command->redirects->next->direction = r_output;
	command->redirects->next->redirector = STDIN_FILENO;
	command->redirects->next->flags = O_CREAT | O_WRONLY;
	command->redirects->next->redirectee.word = ft_strdup("e");

	command->redirects->next->next = malloc(sizeof(t_redirect));
	command->redirects->next->next->id = 2;
	command->redirects->next->next->direction = r_output_append;
	command->redirects->next->next->redirector = STDIN_FILENO;
	command->redirects->next->next->flags = O_CREAT | O_WRONLY | O_APPEND;
	command->redirects->next->next->redirectee.word = ft_strdup("app");
	command->redirects->next->next->next = NULL;

	cmd_executor(command, cmd, av);
	undo_redirections(command);

	return 0;
}
