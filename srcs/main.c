/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:54:26 by rriyas            #+#    #+#             */
/*   Updated: 2022/09/03 00:38:46 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list *freeable = NULL;

/**
 * @brief Function to handle various signals in the program
 *
 * @param sig - signal recieved by the program
 */
void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_lstclear(&freeable, free);
		exit(0);
	}
}

// priority for absolute and then relative path

int execute_cmd(char *cmd, char **argv, char **envp)
{
	// char *PATH;

	(void)cmd;
	(void)argv;
	(void)envp;

	// PATH = getenv("PATH");
	// char **paths = ft_split(PATH, ':');
	// printf("path = %s\n", PATH);
	// for (int i = 0; envp[i]; i++)
	// printf("%s\n", envp[i]);
	return 0;
}

int main(int argc, char **argv, char **envp)
{
	char *s;

	(void)argc;
	(void)argv;
	signal(SIGINT, &sig_handler);
	while (2)
	{
		s = readline(">");
		ft_lstadd_back(&freeable, ft_lstnew(s));
		add_history(s);
		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
		execute_cmd(s, argv, envp);
	}
	return (0);
}