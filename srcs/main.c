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

t_shell	g_krsh;

/**
 * @brief				Function to handle various signals in the program
 *
 * @param sig			Signal recieved by the program
 */
void	sig_handler(int sig)
{
	int	i;

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

void	print_cmd_redirs(t_command *cmd, t_list *iter)
{
	t_redirect	*redir;

	while (iter)
	{
		ft_printf("\t%s\n", (char *)(iter->content));
		iter = iter->next;
	}
	redir = cmd->redirects;
	ft_printf("\nRedirects: %p\n", redir);
	while (redir)
	{
		ft_printf("\t%d : ", redir->direction);
		ft_printf("%s\n", redir->redirectee);
		redir = redir->next;
	}
}

void	display_command(t_command *cmd)
{
	if (!cmd)
	{
		ft_printf("EMPTY COMMAND!\n");
		return ;
	}
	while (cmd)
	{
		ft_printf("id: %d", cmd->id);
		ft_printf("\nWords: %p\n", cmd->words);
		print_cmd_redirs(cmd, cmd->words);
		cmd = cmd->next;
	}
}

// merge adjacent words with quotes
// convert quotes b4 passing toparser

int	get_cmd_size(t_command *cmd)
{
	t_command	*iterator;
	int			i;

	i = 0;
	iterator = cmd;
	while (iterator)
	{
		i++;
		iterator = iterator->next;
	}
	return (i);
}

int	main(int argc, char **argv, char **envp)
{
	char		*s;
	char		**sup;
	t_command	*cmd;
	int			i;

	(void)argc;
	(void)argv;
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
	i = -1;
	g_krsh.env_mngr = generate_env_manager(envp);
	while (TRUE)
	{
		s = readline("minishell ^-^ : ");
		if (s && *s !='\0')
			add_history(s);
		if (!s)
			ft_exit(NULL);
		cmd = parse_input(s);
		g_krsh.num_of_cmds = get_cmd_size(cmd);
		heredoc_handler(cmd);
		executor(cmd);
		free(s);
	}
}
