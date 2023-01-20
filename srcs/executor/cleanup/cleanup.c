/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:04:06 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/20 15:24:57 by rriyas           ###   ########.fr       */
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

	i = 0;
	if (!cmd)
		return ;
	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		free_redirects(temp->redirects);
		ft_lstclear(&(temp->words), free);
		if (temp->argv)
			free(temp->argv);
		if (temp)
			free(temp);
	}
}

void exit_minishell(t_command *cmd, int status)
{
	int i;

	i = 0;
	destroy_dict(g_krsh.env_mngr);
	destroy_dict(g_krsh.declared);
	while (g_krsh.envp[++i])
		free(g_krsh.envp[i]);
	free(g_krsh.envp);
	exit(status);
}