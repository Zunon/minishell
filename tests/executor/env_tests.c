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

int intitiate_testing_env(char **envp)
{
	zundra.envp = envp;
	zundra.env_mngr = generate_env_manager(envp);
}

int test_env_noargs()
{
	int i;
	char *s;
	
	ft_printf("Test %d: env\n", ++t);
	// s = readline("minishell ^-^ : ");
	// int old = dup(STDOUT_FILENO);
	// int fd = open("env_test", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	// dup2(fd, STDOUT_FILENO);
	// ft_env();
	// dup2(old, STDOUT_FILENO);
	// close(old);
	// close(fd);
	// free(s);
	// ft_env();
	return 0;
}

int test_export_no_arg()
{
	ft_printf("\n\nTest %d: export\n", ++t);
	// ft_export(NULL);
	return 0;
}

int test_export_with_args()
{
	return 0;
}

int test_unset_no_args()
{
	return 0;
}

int test_unset_existing_var()
{
	return 0;
}

int test_unset_missing_var()
{
	return 0;
}

int main(int argc, char **argv, char **envp)
{
	intitiate_testing_env(envp);
	test_env_noargs();
	test_export_no_arg();
	test_export_with_args();
	test_unset_no_args();
	test_unset_existing_var();
	test_unset_missing_var();
	return 0;
}