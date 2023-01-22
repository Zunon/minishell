/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:10:48 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/22 07:10:33 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	save_heredoc_to_pipe(t_redirect *iterator, int *index, char **lines)
{
	iterator->here_doc_pipe = *index;
	iterator->redirectee = NULL;
	if (pipe(g_krsh.heredocs[*index]) == -1)
	{
		perror("HEREDOC - Failed to create pipe: ");
		return (EXIT_FAILURE);
	}
	write(g_krsh.heredocs[*index][1], *lines, ft_strlen(*lines));
	if (close(g_krsh.heredocs[*index][1]) == -1)
	{
		perror("HEREDOC - Failed to close pipe write end: ");
		return (EXIT_FAILURE);
	}
	free(*lines);
	(*index)++;
	return (EXIT_SUCCESS);
}

static int	get_num_of_heredocs(t_command *cmd)
{
	t_redirect	*iterator;
	int			heredoc_count;

	heredoc_count = 0;
	while (cmd)
	{
		iterator = cmd->redirects;
		while (iterator)
		{
			if (iterator->direction == HERE_DOC)
				heredoc_count++;
			iterator = iterator->next;
		}
		cmd = cmd->next;
	}
	return (heredoc_count);
}

static void	construct_heredoc_pipes(t_command *pipeline)
{
	int			heredoc_count;
	int			i;

	heredoc_count = get_num_of_heredocs(pipeline);
	g_krsh.heredoc_count = heredoc_count;
	if (heredoc_count == 0)
		return ;
	g_krsh.heredocs = ft_calloc(heredoc_count, sizeof(int *));
	i = 0;
	while (i < heredoc_count)
	{
		g_krsh.heredocs[i] = ft_calloc(2, sizeof(int));
		i++;
	}
}

int	handle_heredoc(t_command *cmd)
{
	t_redirect	*iterator;
	char		*buffer;
	int			index;

	index = 0;
	construct_heredoc_pipes(cmd);
	while (cmd && !g_krsh.blocked)
	{
		iterator = cmd->redirects;
		while (iterator && !g_krsh.blocked)
		{
			if (iterator->direction == HERE_DOC)
			{
				buffer = construct_heredoc(iterator->here_doc_delim);
				if (g_krsh.blocked)
					break ;
				save_heredoc_to_pipe(iterator, &index, &buffer);
			}
			iterator = iterator->next;
		}
		cmd = cmd->next;
	}
	if (g_krsh.blocked == TRUE)
		return (CONTROL_C_INTERRUPT);
	return (EXIT_SUCCESS);
}
