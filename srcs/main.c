/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:54:26 by rriyas            #+#    #+#             */
/*   Updated: 2022/10/23 17:45:51 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_shell zundra;

/**
 * @brief Function to handle various signals in the program
 *
 * @param sig - signal recieved by the program
 */
void sig_handler(int sig)
{
	if (sig == SIGINT) //needs work
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
}



int main(int argc, char **argv, char **envp)
{
	char *s;
	int status_code;
	(void)argc;
	(void)argv;
	(void)envp;
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	zundra.envp = envp;
	while (2)
	{
		s = readline("minishell ^-^ : ");
		add_history(s);
		argv = ft_split(s, ' ');
		c2();
		free(s);
	}
	return (0);
}