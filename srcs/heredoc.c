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

/**
 * @brief	Should work like gnl, looking for the delimiter using the prompt
 * 			expands variables within the prompts with no limits
 * @param	delimiter	string delimiter for the end of the heredoc
 * @return	string that is the full contents of the heredoc
 * @TODO	Expand variables within the result
 * @note	Expansion notes:
 * 				- $ should not terminate if it's a valid variable
 * 				- $USER should terminate without expanding
 * 				- Consider how to allow variable expansion if the delimiter is $
 */
char	*accumulate_heredoc(char *delimiter)
{
	char	*result;
	char	*buffer;
	t_bool	found_delimiter;
	char 	*end;

	found_delimiter = FALSE;
	while (!found_delimiter)
	{
		buffer = readline("> ");
		end = ft_strnstr(buffer, delimiter, ft_strlen(buffer));
		found_delimiter = end != NULL;
		if (!found_delimiter)
			result = ft_strjoin(result, buffer);
		else
			result = ft_strjoin(result, ft_substr(buffer, 0, end - buffer));
	}
	return (result);
}