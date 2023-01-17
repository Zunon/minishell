/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:02:45 by kalmheir          #+#    #+#             */
/*   Updated: 2023/01/17 11:02:50 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_bool is_valid_id_starter(char character)
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
t_bool	has_valid_variable(char *string, size_t *offset)
{
	char *dollar;

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
char	*expand_and_increment(char *string, size_t *offset)
{
	size_t	start;

	start = *offset;
	while (string[*offset] && is_valid_id_starter(string[*offset]))
		*offset = *offset + 1;
	return (expand(ft_substr(string, start, *offset - start)));
}

/**
 * @brief	Expand all valid variables within the given string, and return the
 * 			modified string as a result
 * @param string to be transformed
 * @return	the input string with all valid variables
 */
char	*expand_all_variables(char *string)
{
	char	*result;
	size_t	begin_off;
	size_t	offset;

	offset = 0;
	begin_off = 0;
	result = ft_calloc(1, sizeof(char));
	while (has_valid_variable(string, &offset))
	{
		result = ft_strjoin(result, ft_substr(string, begin_off, offset
			- begin_off - 1));
		result = ft_strjoin(result, expand_and_increment(string, &offset));
		begin_off = offset;
	}
	result = ft_strjoin(result, ft_substr(string, begin_off, offset
		- begin_off));
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
char	*accumulate_heredoc(char *delimiter)
{
	char	*result;
	char	*buffer;
	t_bool	found_delimiter;
	size_t	delim_length;

	found_delimiter = FALSE;
	delim_length = ft_strlen(delimiter);
	while (!found_delimiter)
	{
		buffer = readline("> ");
		found_delimiter = ft_strncmp(delimiter, buffer, delim_length) != 0;
		if (found_delimiter)
			continue ;
		buffer = expand_all_variables(buffer);
		result = ft_strjoin(result, buffer);
	}
	return (result);
}
