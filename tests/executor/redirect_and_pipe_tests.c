/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_and_pipe_tests.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:33:01 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/08 16:33:01 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int t1(/* cat Makefile > b| grep b | <infile grep a > outfile*/)
{
	//CMD 1:
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

	t_word_list *wd1 = malloc(sizeof(t_word_list));
	wd1->curr_word_desc = malloc(sizeof(t_word_desc));
	wd1->curr_word_desc->word = ft_strdup("cat");

	wd1->next = malloc(sizeof(t_word_list));
	wd1->next->curr_word_desc = malloc(sizeof(t_word_desc));
	wd1->next->curr_word_desc->word = ft_strdup("Makefile");

	wd1->next->next = NULL;
	command1->words = wd1;


	// CMD 2:
	t_command *command2 = malloc(sizeof(t_command));
	command2->id = 1;
	command2->fd_in = -1;
	command2->fd_out = -1;
	command2->stdout_old = STDOUT_FILENO;
	command2->stdin_old = STDIN_FILENO;
	command2->redirects = NULL;

	t_word_list *wd2 = malloc(sizeof(t_word_list));
	wd2->curr_word_desc = malloc(sizeof(t_word_desc));
	wd2->curr_word_desc->word = ft_strdup("grep");

	wd2->next = malloc(sizeof(t_word_list));
	wd2->next->curr_word_desc = malloc(sizeof(t_word_desc));
	wd2->next->curr_word_desc->word = ft_strdup("b");

	wd2->next->next = NULL;
	command2->words = wd2;

	// CMD 3:
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
	command3->redirects->next->flags = O_CREAT | O_WRONLY | O_TRUNC;
	command3->redirects->next->redirectee.word = ft_strdup("outfile");
	command3->redirects->next->next = NULL;

	t_word_list *wd3 = malloc(sizeof(t_word_list));
	wd3->curr_word_desc = malloc(sizeof(t_word_desc));
	wd3->curr_word_desc->word = ft_strdup("grep");

	wd3->next = malloc(sizeof(t_word_list));
	wd3->next->curr_word_desc = malloc(sizeof(t_word_desc));
	wd3->next->curr_word_desc->word = ft_strdup("a");

	wd3->next->next = NULL;
	command3->words = wd3;


	command1->next = command2;
	command2->next = command3;
	command3->next = NULL;
	zundra.num_of_cmds = 3;
	executor(command1);
	return 0;
}

int t2(/*cat /dev/random | head -n 10 > rand */)
{
	zundra.num_of_cmds = 2;
	t_command *command1 = malloc(sizeof(t_command));
	command1->fd_in = -1;
	command1->fd_out = -1;
	command1->stdout_old = STDOUT_FILENO;//dup(STDOUT_FILENO);
	command1->stdin_old = STDIN_FILENO; //dup(STDIN_FILENO);
	command1->id = 0;
	command1->redirects = NULL;

	t_word_list *wd1 = malloc(sizeof(t_word_list));
	wd1->curr_word_desc = malloc(sizeof(t_word_desc));
	wd1->curr_word_desc->word = ft_strdup("cat");

	wd1->next = malloc(sizeof(t_word_list));
	wd1->next->curr_word_desc = malloc(sizeof(t_word_desc));
	wd1->next->curr_word_desc->word = ft_strdup("/dev/random");

	wd1->next->next = NULL;
	command1->words = wd1;

	// CMD 2:
	t_command *command2 = malloc(sizeof(t_command));
	command2->id = 1;
	command2->fd_in = -1;
	command2->fd_out = -1;
	command2->stdout_old = STDOUT_FILENO;
	command2->stdin_old = STDIN_FILENO;
	command2->redirects = malloc(sizeof(t_redirect));

	command2->redirects->direction = r_output;
	command2->redirects->redirector = STDIN_FILENO;
	command2->redirects->flags = O_CREAT | O_WRONLY | O_TRUNC;
	command2->redirects->redirectee.word = ft_strdup("rand");
	command2->redirects->next = NULL;

	t_word_list *wd2 = malloc(sizeof(t_word_list));
	wd2->curr_word_desc = malloc(sizeof(t_word_desc));
	wd2->curr_word_desc->word = ft_strdup("head");

	wd2->next = malloc(sizeof(t_word_list));
	wd2->next->curr_word_desc = malloc(sizeof(t_word_desc));
	wd2->next->curr_word_desc->word = ft_strdup("-n");

	wd2->next->next = malloc(sizeof(t_word_list));
	wd2->next->next->curr_word_desc = malloc(sizeof(t_word_desc));
	wd2->next->next->curr_word_desc->word = ft_strdup("10");
	wd2->next->next->next = NULL;
	command2->words = wd2;

	command1->next = command2;
	command2->next = NULL;
	executor(command1);
}
int main(int argc, char **argv, char **envp)
{
	// intitiate_testing_env(envp);
	// test_env_noargs();
	// test_export_no_arg();
	// test_export_with_args();
	// test_unset_no_args();
	// test_unset_existing_var();
	// test_unset_missing_var();
    t1();
    write(1, "\n", 1);
    t2();
	return 0;
}