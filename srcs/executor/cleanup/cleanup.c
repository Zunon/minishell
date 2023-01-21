/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:04:06 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/21 19:38:39 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief			Function to deallocate memory for the linked list of redirections
 * 					belongin to any command
 *
 * @param redir		Linked list of redirections for the command
 */
static void	free_redirects(t_redirect *redir)
{
	t_redirect	*temp;

	if (!redir)
		return ;
	while (redir)
	{
		temp = redir;
		redir = redir->next;
		if (temp->direction == HERE_DOC)
			free(temp->here_doc_delim);
		if (temp->redirectee)
			free(temp->redirectee);
		free(temp);
	}
}

/**
 * @brief			Function to deallocate memory for a linked list of commands
 * 					in a pipeline
 *
 * @param cmd		Linked list of commands
 */
void	free_commands(t_command *cmd)
{
	t_command	*temp;
	int			i;

	if (g_krsh.last_child_pid == -1)
		write(STDERR_FILENO, "CHILD ___ freeing cmds from  shell\n", 36);
	else
		write(STDERR_FILENO, "PARENT ___ freeing cmds from  shell\n", 37);
	if (!cmd)
		return ;
	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		free_redirects(temp->redirects);
		ft_lstclear(&(temp->words), &free);
		if (temp->argv)
			free(temp->argv);
		free(temp);

	}
	i = 0;
	while (i < g_krsh.heredoc_count)
	{
		free(g_krsh.heredocs[i]);
		i++;
	}
	if (g_krsh.heredoc_count > 0)
		free(g_krsh.heredocs);
}

void	exit_minishell(t_command **cmd, int status)
{
	int	i;

	i = -1;
	if (g_krsh.last_child_pid == -1)
		write(STDERR_FILENO, "CHILD ___ exiting shell\n", 25);
	else
		write(STDERR_FILENO, "PARENT ___ exiting shell\n", 26);
	free_commands(*cmd);
	*cmd = NULL;
	destroy_dict(&g_krsh.env_mngr);
	destroy_dict(&g_krsh.declared);
	while (g_krsh.envp[++i])
		free(g_krsh.envp[i]);
	free(g_krsh.envp);
	exit(status);
}
