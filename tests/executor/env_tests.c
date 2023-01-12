/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:09:10 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/05 17:07:07 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/dictionary.h"

t_shell zundra;
int t = 0;

void intitiate_testing_env(char **envp)
{
	zundra.envp = envp;
	zundra.env_mngr = generate_env_manager(envp);
}

int test_env_noargs()
{
	ft_printf("\n\nTest %d: env\n", ++t);
	zundra.num_of_cmds = 1;
	t_command *command1 = malloc(sizeof(t_command));
	command1->fd_in = -1;
	command1->fd_out = -1;
	command1->id = 0;
	command1->redirects = NULL;

	t_word_list *wd1 = malloc(sizeof(t_word_list));
	wd1->curr_word_desc = malloc(sizeof(t_word_desc));
	wd1->curr_word_desc->word = ft_strdup("env");

	wd1->next = NULL;
	command1->words = wd1;
	command1->next = NULL;
	executor(command1);
	return 0;
}

int test_export_no_arg()
{
	ft_printf("\n\nTest %d: export\n", ++t);
	zundra.num_of_cmds = 1;
	t_command *command1 = malloc(sizeof(t_command));
	command1->fd_in = -1;
	command1->fd_out = -1;
	command1->id = 0;
	command1->redirects = NULL;

	t_word_list *wd1 = malloc(sizeof(t_word_list));
	wd1->curr_word_desc = malloc(sizeof(t_word_desc));
	wd1->curr_word_desc->word = ft_strdup("export");

	wd1->next = NULL;
	command1->words = wd1;
	command1->next = NULL;
	executor(command1);
	return 0;
}

int test_export_with_args()
{
	ft_printf("\n\nTest %d: export a=b\n", ++t);
	zundra.num_of_cmds = 1;
	t_command *command1 = malloc(sizeof(t_command));
	command1->fd_in = -1;
	command1->fd_out = -1;
	command1->id = 0;
	command1->redirects = NULL;

	t_word_list *wd1 = malloc(sizeof(t_word_list));
	wd1->curr_word_desc = malloc(sizeof(t_word_desc));
	wd1->curr_word_desc->word = ft_strdup("export");

	wd1->next = malloc(sizeof(t_word_list));
	wd1->next->curr_word_desc = malloc(sizeof(t_word_desc));
	wd1->next->curr_word_desc->word = ft_strdup("a");
	wd1->next->curr_word_desc->assignment = 1;

	wd1->next->next = malloc(sizeof(t_word_list));
	wd1->next->next->curr_word_desc = malloc(sizeof(t_word_desc));
	wd1->next->next->curr_word_desc->word = ft_strdup("b");
	wd1->next->next->next=NULL;
	command1->words = wd1;
	command1->next = NULL;
	executor(command1);
	return 0;
}

int test_unset_no_args()
{
	ft_printf("\n\nTest %d: unset\n", ++t);
	zundra.num_of_cmds = 1;
	t_command *command1 = malloc(sizeof(t_command));
	command1->fd_in = -1;
	command1->fd_out = -1;
	command1->id = 0;
	command1->redirects = NULL;

	t_word_list *wd1 = malloc(sizeof(t_word_list));
	wd1->curr_word_desc = malloc(sizeof(t_word_desc));
	wd1->curr_word_desc->word = ft_strdup("unset");

	wd1->next = NULL;
	command1->words = wd1;
	command1->next = NULL;
	executor(command1);
	return 0;
}

int test_unset_existing_var()
{
	ft_printf("\n\nTest %d: unset a=b\n", ++t);
	zundra.num_of_cmds = 1;
	t_command *command1 = malloc(sizeof(t_command));
	command1->fd_in = -1;
	command1->fd_out = -1;
	command1->id = 0;
	command1->redirects = NULL;

	t_word_list *wd1 = malloc(sizeof(t_word_list));
	wd1->curr_word_desc = malloc(sizeof(t_word_desc));
	wd1->curr_word_desc->word = ft_strdup("unset");

	wd1->next = malloc(sizeof(t_word_list));
	wd1->next->curr_word_desc = malloc(sizeof(t_word_desc));
	wd1->next->curr_word_desc->word = ft_strdup("a");
	wd1->next->curr_word_desc->assignment = 1;

	wd1->next->next = malloc(sizeof(t_word_list));
	wd1->next->next->curr_word_desc = malloc(sizeof(t_word_desc));
	wd1->next->next->curr_word_desc->word = ft_strdup("b");
	wd1->next->next->next=NULL;
	command1->words = wd1;
	command1->next = NULL;
	executor(command1);
	return 0;
}

int test_unset_missing_var()
{
	ft_printf("\n\nTest %d: unset x\n", ++t);
	zundra.num_of_cmds = 1;
	t_command *command1 = malloc(sizeof(t_command));
	command1->fd_in = -1;
	command1->fd_out = -1;
	command1->id = 0;
	command1->redirects = NULL;

	t_word_list *wd1 = malloc(sizeof(t_word_list));
	wd1->curr_word_desc = malloc(sizeof(t_word_desc));
	wd1->curr_word_desc->word = ft_strdup("unset");

	wd1->next = malloc(sizeof(t_word_list));
	wd1->next->curr_word_desc = malloc(sizeof(t_word_desc));
	wd1->next->curr_word_desc->word = ft_strdup("x");
	wd1->next->next =NULL;
	command1->words = wd1;
	command1->next = NULL;
	executor(command1);
	return 0;
}

// int main(int argc, char **argv, char **envp)
// {
// 	intitiate_testing_env(envp);
// 	test_env_noargs();
// 	test_export_no_arg();
// 	test_export_with_args();
// 	test_env_noargs();
// 	test_unset_no_args();
// 	test_env_noargs();
// 	test_unset_existing_var();
// 	test_env_noargs();
// 	test_unset_missing_var();
// 	test_env_noargs();

// 	return 0;
// }