/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:18:19 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/05 16:20:29 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int t1 (/* cat Makefile > a >> b >> c*/)
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
	command->redirects->direction = r_output;
	command->redirects->redirector = STDIN_FILENO;
	command->redirects->flags = O_CREAT | O_WRONLY | O_TRUNC;
	command->redirects->redirectee.word = ft_strdup("a");

	command->redirects->next = malloc(sizeof (t_redirect));
	command->redirects->next->direction = r_output;
	command->redirects->next->redirector = STDIN_FILENO;
	command->redirects->next->flags = O_CREAT | O_WRONLY | O_APPEND;
	command->redirects->next->redirectee.word = ft_strdup("b");

	command->redirects->next->next = malloc(sizeof(t_redirect));
	command->redirects->next->next->direction = r_output;
	command->redirects->next->next->redirector = STDIN_FILENO;
	command->redirects->next->next->flags = O_CREAT | O_WRONLY | O_APPEND;
	command->redirects->next->next->redirectee.word = ft_strdup("c");
	command->redirects->next->next->next = NULL;

	return 0;
}

int t2(/* <d grep a > e >> app */)
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
	command->redirects->direction = r_input;
	command->redirects->redirector = STDIN_FILENO;
	command->redirects->flags = O_RDONLY;
	command->redirects->redirectee.word = ft_strdup("d");

	command->redirects->next = malloc(sizeof(t_redirect));
	command->redirects->next->direction = r_output;
	command->redirects->next->redirector = STDIN_FILENO;
	command->redirects->next->flags = O_CREAT | O_WRONLY;
	command->redirects->next->redirectee.word = ft_strdup("e");

	command->redirects->next->next = malloc(sizeof(t_redirect));
	command->redirects->next->next->direction = r_output_append;
	command->redirects->next->next->redirector = STDIN_FILENO;
	command->redirects->next->next->flags = O_CREAT | O_WRONLY | O_APPEND;
	command->redirects->next->next->redirectee.word = ft_strdup("app");
	command->redirects->next->next->next = NULL;

	cmd_executor(command, av);

	return 0;
}

int t3(/* cat Makefile > b| grep b | <infile grep b > outfile*/)
{
	//CMD 1:
	char *cmd1 = ft_strdup("cat");
	char **av1 = malloc(sizeof(char *) * 3);
	av1[0] = ft_strdup("cat");
	av1[1] = ft_strdup("Makefile");
	av1[2] = NULL;
	t_command *command1 = malloc(sizeof(t_command));
	command1->fd_in = -1;
	command1->fd_out = -1;
	command1->stdout_old = STDOUT_FILENO;//dup(STDOUT_FILENO);
	command1->stdin_old = STDIN_FILENO; //dup(STDIN_FILENO);
	command1->id = 0;
	command1->redirects = malloc(sizeof(t_redirect));
	command1->redirects->direction = r_output;
	command1->redirects->redirector = STDIN_FILENO;
	command1->redirects->flags = O_CREAT | O_WRONLY;
	command1->redirects->redirectee.word = ft_strdup("b");
	command1->redirects->next = NULL;

	// CMD 2:
	char *cmd2 = ft_strdup("grep");
	char **av2 = malloc(sizeof(char *) * 3);
	av2[0] = ft_strdup("grep");
	av2[1] = ft_strdup("b");
	av2[2] = NULL;
	t_command *command2 = malloc(sizeof(t_command));
	command2->id = 1;
	command2->fd_in = -1;
	command2->fd_out = -1;
	command2->stdout_old = STDOUT_FILENO;
	command2->stdin_old = STDIN_FILENO;
	command2->redirects = NULL;

	// CMD 3:
	char *cmd3 = ft_strdup("grep");
	char **av3 = malloc(sizeof(char *) * 3);
	av3[0] = ft_strdup("grep");
	av3[1] = ft_strdup("b");
	av3[2] = NULL;
	t_command *command3 = malloc(sizeof(t_command));
	command3->id = 2;
	command3->fd_in = -1;
	command3->fd_out = -1;
	command3->stdout_old = STDOUT_FILENO;
	command3->stdin_old = STDIN_FILENO;
	command3->redirects = malloc(sizeof(t_redirect));
	command3->redirects->direction = r_input;
	command3->redirects->redirector = STDIN_FILENO;
	command3->redirects->flags = O_CREAT | O_RDONLY;
	command3->redirects->redirectee.word = ft_strdup("infile");
	command3->redirects->next = malloc(sizeof(t_redirect));

	command3->redirects->next->direction = r_output;
	command3->redirects->next->redirector = STDIN_FILENO;
	command3->redirects->next->flags = O_CREAT | O_WRONLY;
	command3->redirects->next->redirectee.word = ft_strdup("outfile");
	command3->redirects->next->next = NULL;

	command1->next = command2;
	command2->next = command3;
	command3->next = NULL;
	zundra.num_of_cmds = 3;
	zundra.pipes[0][0] = STDIN_FILENO;
	zundra.pipes[0][1] = STDOUT_FILENO;
	zundra.pipes[3][0] = STDIN_FILENO;
	zundra.pipes[3][1] = STDOUT_FILENO;
	for (int i = 0 ; i< 4; i++)
		if (i != 0 && i != 3)
			pipe(zundra.pipes[i]);

	cmd_executor(command1, av1);
	cmd_executor(command2, av2);
	cmd_executor(command3, av3);

	for (int i = 1; i < zundra.num_of_cmds; i++)
	{
		close(zundra.pipes[i][0]);
		close(zundra.pipes[i][1]);
	}
	for (int i = 0; i< zundra.num_of_cmds; i++)
		wait(0);

	return 0;
}

int t4()
{
	t_command *command1 = malloc(sizeof(t_command));
	command1->fd_in = -1;
	command1->fd_out = -1;
	command1->stdout_old = STDOUT_FILENO;
	command1->stdin_old = STDIN_FILENO;
	command1->id = 0;
	command1->redirects = NULL;
	command1->next = NULL;
	zundra.num_of_cmds = 1;

	t_word_list *wd = malloc(sizeof(t_word_list));
	wd->curr_word_desc = malloc(sizeof(t_word_desc));
	wd->curr_word_desc->word = ft_strdup("cat");

	wd->next = malloc(sizeof(t_word_list));
	wd->next->curr_word_desc = malloc(sizeof(t_word_desc));
	wd->next->curr_word_desc->word = ft_strdup("Makefile");

	wd->next->next = NULL;
	// malloc(sizeof(t_word_list));
	// wd->next->next->curr_word_desc = malloc(sizeof(t_word_desc));
	// wd->next->next->curr_word_desc->word = ft_strdup("");
	// wd->next->next->next = NULL;

	command1->words = wd;
	executor(command1);
	return (0);
}
