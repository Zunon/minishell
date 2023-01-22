/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 06:46:51 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/22 06:52:13 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_krsh.blocked = TRUE;
		rl_on_new_line();
		rl_redisplay();
		write(STDERR_FILENO, "  \n", 4);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_printf("Press enter to exit:");
		g_krsh.status_code = CONTROL_C_INTERRUPT;
	}
}

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
	signal(SIGINT, &heredoc_sig_handler);
	result = get_heredoc_str(delimiter, result, delim_length);
	if (g_krsh.blocked)
	{
		free(result);
		result = NULL;
	}
	signal(SIGINT, &sig_handler);
	return (result);
}
