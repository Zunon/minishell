/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:10:48 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/17 20:10:48 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief			Function to generate a temp file that stores the
 * 					heredoc buffer
 * 
 * @return char*	Filename generated by function
 */
char	*generate_heredoc_fname(void)
{
	char	*fname;
	char	*suffix;
	char	*temp;
	int		i;

	fname = ft_strdup("__temp");
	i = 0;
	while (access(fname, F_OK) == 0)
	{
		suffix = ft_itoa(i);
		temp = fname;
		fname = ft_strjoin(fname, suffix);
		free(temp);
		free(suffix);
		i++;
	}
	return (fname);
}

/**
 * @brief			Save heredoc input to a temp file 
 * 
 * @param lines		Array of strings entered by user in heredoc
 * @return char*	Name of temp file used to store heredoc buffer
 */
char	*save_heredoc_input(char *lines)
{
	int		fd;
	char	*fname;

	fname = generate_heredoc_fname();
	fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("HEREDOC - Error while opening temp file");
		return (NULL);
	}
	write(fd, lines, ft_strlen(lines));
	if (close(fd) == -1)
	{
		perror("HEREDOC - Error while closing temp output file: ");
		return (NULL);
	}
	return (fname);
}

void	heredoc_handler(t_command *cmd)
{
	t_redirect	*iterator;
	char		*buffer;

	while (cmd)
	{
		iterator = cmd->redirects;
		while (iterator)
		{
			if (iterator->direction == HERE_DOC)
			{
				buffer = accumulate_heredoc(iterator->here_doc_delim);
				iterator->redirectee = save_heredoc_input(buffer);
			}
			iterator = iterator->next;
		}
		cmd = cmd->next;
	}
}
