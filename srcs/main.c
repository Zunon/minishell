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

static void	print_cmd_redirs(t_command *cmd, t_list *iter)
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

static void	control_d_exit(void)
{
	int	i;

	i = -1;
	destroy_dict(&g_krsh.env_mngr);
	destroy_dict(&g_krsh.declared);
	while (g_krsh.envp[++i])
		free(g_krsh.envp[i]);
	free(g_krsh.envp);
	exit(EXIT_SUCCESS);
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
	g_krsh.status_code = EXIT_SUCCESS;
	cmd = NULL;
	while (TRUE)
	{
		s = readline("〈krsh〉λ ⇾  ");
		if (s && *s != '\0')
			add_history(s);
		if (!s)
			exit_minishell(cmd, g_krsh.status_code);
		cmd = parse_input(s);
		free(s);
		g_krsh.blocked = FALSE;
		executor(cmd);
		free_commands(cmd);
		cmd = NULL;
	}
}
