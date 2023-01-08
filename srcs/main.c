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
		write(2, "  \n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == 3)
	{
		// free_commands(zundra.cmds);
		destroy_dict(zundra.env_mngr);
		while (zundra.envp[++i])
			free(zundra.envp[i]);
		free(zundra.envp);
		exit(0);
	}
}

/**
 * @brief				Phase 1 of the shell - commands typed by th user are split into tokens
 *
 */
void lexer(char **argv)
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
	t_command *cmd;

	(void)argc;
	(void)argv;
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	zundra.env_mngr = generate_env_manager(envp);
	while (2)
	{
		s = readline("minishell ^-^ : ");
		add_history(s);
		lexer(argv);
		cmd = parser();
		executor(cmd);
		free(s);
	}
	return (0);
}