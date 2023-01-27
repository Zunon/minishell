/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 06:46:51 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/27 11:39:48 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	*get_heredoc_str(const char *delimiter, char *result,
		size_t delim_length)
{
	char	*buffer;
	t_bool	found_delimiter;

	found_delimiter = FALSE;
	while (!found_delimiter && !g_krsh.blocked)
	{
		buffer = readline("> ");
		if (!buffer)
			break ;
		found_delimiter = ft_strncmp(delimiter, buffer, delim_length + 1) == 0;
		if (found_delimiter)
			break ;
		buffer = expand_all_variables(buffer);
		buffer = join_and_free(buffer, "\n", TRUE, FALSE);
		result = join_and_free(result, buffer, TRUE, TRUE);
	}
	return (result);
}

/**
 * @brief	Should work like gnl, looking for the delimiter using the prompt
 * 			expands variables within the prompts with no limits
 * @param	delimiter	string delimiter for the end of the heredoc
 * @return	string that is the full contents of the heredoc
 * @note	Expansion notes:
 * 				- Check if delimiter is the entire line
 * 				- Expand variables
 * 				- Join into result
 * 				- $? should be expanded
 * @note <CTRL-D> could take the delimiter's place.
 */
char	*construct_heredoc(char *delimiter)
{
	char	*result;
	size_t	delim_length;

	delim_length = ft_strlen(delimiter);
	result = ft_strdup("");
	signal(SIGINT, SIG_IGN);
	result = get_heredoc_str(delimiter, result, delim_length);
	if (g_krsh.blocked)
	{
		free(result);
		result = NULL;
	}
	signal(SIGINT, &sig_handler);
	return (result);
}
