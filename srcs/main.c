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

t_token	*init_ends(t_token *list)
{
	t_token	*pretail;
	t_token	*tail;

	list->prev = ft_calloc(1, sizeof(t_token));
	pretail = token_last(list);
	pretail->next = ft_calloc(1, sizeof(t_token));
	tail = pretail->next;
	*(list->prev) = (t_token){HEAD, ft_strdup("head"), list, NULL};
	*tail = (t_token){TAIL, ft_strdup("tail"), NULL, pretail};
	return (tail);
}

t_token	*clear_ends(t_token *list, t_token *head, t_token *tail)
{
	if (head == list)
	{
		list = list->next;
		(tail->prev)->next = NULL;
		free(head->contents);
		free(head);
		free(tail->contents);
		free(tail);
	}
	else
	{
		head = list;
		tail = token_last(list);
		list = head->next;
		tail->prev->next = NULL;
		free(head->contents);
		free(head);
		free(tail->contents);
		free(tail);
	}
	list->prev = NULL;
	token_last(list)->next = NULL;
	return (list);
}

int	main(int argc, char **argv, char **envp)
{
	char		*s;
	t_command	*cmd;

	(void)argc;
	(void)argv;
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
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
