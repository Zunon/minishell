/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:02:45 by kalmheir          #+#    #+#             */
/*   Updated: 2023/01/22 06:27:41 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_bool	is_valid_id_starter(char character)
{
	return (character == '?' || character == '_' || ft_isalpha(character));
}

/**
 * @brief	Scans the string for the next valid variable and returns whether or
 * 			not it exists, incrementing the offset to the variable name if found
 * 			, incrementing it to the null terminator if not found.
 * @param string	String to be searched through
 * @param offset	unsigned integer for the offset from the beginning of string
 * @return	boolean indicating if there was a variable found
 */
static t_bool	has_valid_variable(char *string, size_t *offset)
{
	char	*dollar;

	while (string[*offset])
	{
		dollar = ft_strchr(string + *offset, '$');
		if (dollar == NULL)
			break ;
		*offset = dollar - string + 1;
		if (string[*offset] && is_valid_id_starter(string[*offset]))
			return (TRUE);
	}
	*offset = ft_strchr(string, '\0') - string;
	return (FALSE);
}

/**
 * @brief	returns the expanded form of the variable whose name begins at the
 * 			offset, while incrementing offset based on the name
 * @param string	string to be looked into
 * @param offset	offset of the name of the variable
 * @return	expanded form of the variable
 */
static char	*expand_and_increment(char *string, size_t *offset)
{
	size_t	start;
	char	*name;
	char	*value;

	start = *offset;
	while (string[*offset] && is_valid_id_starter(string[*offset]))
		*offset = *offset + 1;
	name = ft_substr(string, start, *offset - start);
	value = expand(name);
	free(name);
	return (value);
}

/**
 * @brief	Expand all valid variables within the given string, and return the
 * 			modified string as a result
 * @param string to be transformed
 * @return	the input string with all valid variables
 */
static char	*expand_all_variables(char *string)
{
	char	*result;
	size_t	begin_off;
	size_t	offset;

	offset = 0;
	begin_off = 0;
	result = ft_calloc(1, sizeof(char));
	while (has_valid_variable(string, &offset))
	{
		result = join_and_free(result, ft_substr(string, begin_off, offset
					- begin_off - 1), TRUE, TRUE);
		result = join_and_free(result, expand_and_increment(string, &offset),
				TRUE, TRUE);
		begin_off = offset;
	}
	result = join_and_free(result, ft_substr(string, begin_off, offset
				- begin_off), TRUE, TRUE);
	free(string);
	return (result);
}

void	heredoc_sig_handler(int sig)
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

char	*get_heredoc_str(const char *delimiter, char *result,
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
