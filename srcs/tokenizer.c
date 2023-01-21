/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:59:18 by kalmheir          #+#    #+#             */
/*   Updated: 2023/01/22 00:24:11 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief			Get the token type based on the character passed.
 * 					This function is called by get_next_token to ascertain
 * 					the type of the token based on the first character of the line
 *
 * @param ch
 * @return			enum e_token_type
 */
enum e_token_type	get_token_type(char ch)
{
	if (ch == '\'')
		return (SINGLE_QUOTE);
	if (ch == '"')
		return (DOUBLE_QUOTE);
	if (ch == '$')
		return (VARIABLE);
	if (ch == ' ' || (ch >= '\t' && ch <= 12))
		return (WHITESPACE);
	if (ch == '|')
		return (PIPE);
	if (ch == '>' || ch == '<')
		return (REDIRECTION);
	return (WORD);
}

void	go_to_eov(int *i, const char *str, enum e_token_type *type)
{
	if (!*str || (!is_valid_id_starter(*str) && *str != '\'' && *str != '"'))
		*type = WORD;
	if (*str != '?')
		while (str[*i - 1] && get_token_type(str[*i - 1]) == WORD)
			*i = *i + 1;
	else
		*i = 3;
}

/**
 * @brief			Construct the first token object (if any) of the line
 * 					passed to the function
 *
 * @param line		string to extract tokens from
 * @return t_token*	Token struct containing information about the first token
 * 					of the line
 */
t_token	*get_next_token(char *line)
{
	char				*token_string;
	t_token				*tok;
	enum e_token_type	first;
	int					i;

	if (!line || !*line)
		return (NULL);
	tok = ft_calloc(1, sizeof(t_token));
	first = get_token_type(line[0]);
	i = 1;
	if (first == VARIABLE)
		go_to_eov(&i, line + 1, &first);
	else if (first == WORD || first == WHITESPACE)
		while (line[i] && get_token_type(line[i]) == first)
			i++;
	else if (first == REDIRECTION && get_token_type(line[i]) == first)
		i++;
	if (!i)
		i++;
	token_string = ft_substr(line, 0, i);
	*tok = (t_token){first, token_string, NULL, NULL};
	return (tok);
}

/**
 * @brief Turn the input string into a list of tokens by calling get_next_token
 * @param input string
 * @return linked list of tokens to be processed further
 */
t_token	*preprocess_input(char *input)
{
	t_token	*result;
	t_token	*iterator;
	size_t	offset;

	result = get_next_token(input);
	iterator = result;
	offset = ft_strlen(iterator->contents);
	while (iterator)
	{
		iterator->next = get_next_token(input + offset);
		if (iterator->next)
		{
			iterator->next->prev = iterator;
			offset += ft_strlen(iterator->next->contents);
		}
		iterator = iterator->next;
	}
	return (result);
}

/**
 * @brief Turn a string into a list of tokens
 * @param input - input string
 * @return Linked list of token nodes
 *
 * @note - We will perform env variable expansion, group single quote strings as
 * one token and combine double quote strings after expansion, split tokens such
 * as "hello or |>
 * steps:
 * - Preprocess input, removing whitespace
 * - Tokenize:
 *  - Construct tokens [get_next_token()]
 *  - Build them into a list [preprocess_input()]
 *  - Group together single-quoted strings
 *  - Expand any variables and replace the corresponding token
 *  - Group together double-quoted strings
 * - Return list
 */
t_token	*tokenize(char *input)
{
	t_token	*list;

	if (!input || !*input)
		return (NULL);
	list = preprocess_input(input);
	list = collapse_quotes(SINGLE_QUOTE, list);
	list = discard_dollar(list);
	list = expand_variables(list);
	list = collapse_quotes(DOUBLE_QUOTE, list);
	list = merge_words(list);
	list = split_words_on_whitespace(list);
	list = discard_whitespace(list);
	list = disquote(list);
	list->prev = NULL;
	token_last(list)->next = NULL;
	print_tokens(list);
	return (list);
}
