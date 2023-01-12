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
 * @brief				Function to handle various signals in the program
 *
 * @param sig			Signal recieved by the program
 */
void sig_handler(int sig)
{
	int i;

	i = -1;
	if (sig == SIGINT) //needs work
	{
		rl_on_new_line();
		rl_redisplay();
		write(2, "  \n", 4);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		zundra.status_code = CONTROL_C_INTERRUPT;
	}
	if (sig == 4)
	{
		destroy_dict(zundra.env_mngr);
		while (zundra.envp[++i])
			free(zundra.envp[i]);
		free(zundra.envp);
		exit(EXIT_SUCCESS);
	}
}

/**
 * @brief				Phase 1 of the shell - commands typed by th user are split into tokens
 *
 */
void lexer(char *argv)
{
	(void)argv;
}

/**
 * @brief				Phase 2 of the shell - parsing of tokens generated by the lexer happens here
 *
 * @return t_command*	Linked list of commands in the current pipeline
 */
t_command *parser()
{
	return NULL;
}


int main(int argc, char **argv, char **envp)
{
	char *s;
	char **sup;
	t_command *cmd;

	(void)argc;
	(void)argv;
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
	zundra.env_mngr = generate_env_manager(envp);
	while (2)
	{
		s = readline("minishell ^-^ : ");
		add_history(s);
		if (!s)					/* Control D check */
			ft_exit(NULL);
		// lexer(s);
		// cmd = parser();
		// executor(cmd);
		// ft_exit(argv);
		free(s);
	}
	ft_exit(sup);
	return (0);
}