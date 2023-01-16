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

t_shell g_krsh;

/**
 * @brief				Function to handle various signals in the program
 *
 * @param sig			Signal recieved by the program
 */
void sig_handler(int sig)
{
	int i;

	i = -1;
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(2, "  \n", 4);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_krsh.status_code = CONTROL_C_INTERRUPT;
	}
	if (sig == 4)
	{
		destroy_dict(g_krsh.env_mngr);
		while (g_krsh.envp[++i])
			free(g_krsh.envp[i]);
		free(g_krsh.envp);
		exit(EXIT_SUCCESS);
	}
}

void display_command(t_command *cmd)
{
	if (!cmd)
	{
		ft_printf("EMPTY COMMAND!\n");
		return;
	}
	while (cmd)
	{
		ft_printf("id: %d", cmd->id);
		t_list *iter = cmd->words;
		ft_printf("\nWords: %p\n", iter);
		while (iter)
		{
			ft_printf("\t%s\n", (char *)(iter->content));
			iter = iter->next;
		}
		t_redirect *redir = cmd->redirects;
		ft_printf("\nRedirects: %p\n", redir);
		while (redir)
		{
			ft_printf("\t%d : ", redir->direction);
			ft_printf("%s\n", redir->redirectee);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

// merge adjacent words with quotes
// convert quotes b4 passing toparser

int get_cmd_size(t_command *cmd)
{
	t_command *iterator;
	int i;

	i = 0;
	iterator = cmd;
	while (iterator)
	{
		i++;
		iterator = iterator->next;
	}
	return (i);
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
	int i;
	i = -1;
	g_krsh.env_mngr = generate_env_manager(envp);
	while (TRUE)
	{
		s = readline("minishell ^-^ : ");
		add_history(s);
		if (!s) /* Control D check */
			ft_exit(NULL);
		cmd = parse_input(s);
		g_krsh.num_of_cmds = get_cmd_size(cmd);
		executor(cmd);
		free(s);
	}
	ft_exit(sup);
	return (0);
}
