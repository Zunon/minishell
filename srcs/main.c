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

int main(int argc, char **argv, char **envp)
{
	char *s;

	(void)argc;
	(void)argv;
	(void)envp;
	signal(SIGINT, &sig_handler);
	while (2)
	{
		s = readline("minishell ^-^ : ");
		ft_lstadd_back(&freeable, ft_lstnew(s));
		add_history(s);
		argv = ft_split(s, ' ');
		execute_cmd(argv[0], argv, envp);
	}
	return (0);
}