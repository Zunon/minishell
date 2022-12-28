/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:18:19 by rriyas            #+#    #+#             */
/*   Updated: 2022/12/28 16:45:37 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int test_output_redirect(char *cmd, char **argv, char **envp)
{
	int std_old;
	char **av = malloc(5 * sizeof(char *));
	av[0] = ft_strdup("cat");
	av[1] = ft_strdup("Makefile");
	av[2] = ft_strdup(">");
	av[3] = ft_strdup("outfile.txt");
	av[4] = NULL;
	zundra.fd = open(argv[3], O_WRONLY | O_CREAT, 0777);
	std_old = dup(STDOUT_FILENO);
	dup2(zundra.fd, STDOUT_FILENO);
	execute_cmd(cmd, av, envp, 0);
	close(zundra.fd);
	dup2(std_old, STDOUT_FILENO);
	close(std_old);
	return 0;
}

int test_cmd1(char *cmd, char **argv, char **envp)
{
	int std_old;
	char **av = malloc(3 * sizeof(char *));
	av[0] = ft_strdup("cat");
	av[1] = ft_strdup("infile");
	av[2] = NULL;
	zundra.fd = open(argv[1], O_RDONLY | O_CREAT, 0777);
	std_old = dup(STDIN_FILENO);
	dup2(zundra.fd, STDIN_FILENO);
	execute_cmd(av[0], av, envp, 0);
	close(zundra.fd);
	dup2(std_old, STDIN_FILENO);
	close(std_old);
	return 0;
}

int test_cmd2(char *cmd, char **argv, char **envp)
{
	int std_old;
	char **av = malloc(3 * sizeof(char *));
	av[0] = ft_strdup("grep");
	av[1] = ft_strdup("1");
	av[2] = NULL;
	execute_cmd(av[0], av, envp, 1);
	return 0;
}

int test_cmd3(char *cmd, char **argv, char **envp)
{
	int std_old;
	char **av = malloc(3 * sizeof(char *));
	av[0] = ft_strdup("grep");
	av[1] = ft_strdup("3");
	av[2] = NULL;
	execute_cmd(av[0], av, envp, 1);
	return 0;
}