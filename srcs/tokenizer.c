#include "../inc/minishell.h"

/**
 * @brief			Get the token type based on the character passed.
 * 					This function is called by get_next_token to ascertain
 * 					the type of the token based on the first character of the line
 *
 * @param ch
 * @return			enum e_token_type
 */
enum e_token_type get_token_type(char ch)
{
	if (ch == '\'')
		return (SINGLE_QUOTE);
	if (ch == '\"')
		return (DOUBLE_QUOTE);
	if (ch == '$')
		return (VARIABLE);
	if (ft_isalpha(ch) || ft_isdigit(ch))
			return (WORD);
	if (ft_iswhitespace(ch))
		return (WHITESPACE);
	if (ch == '|')
		return (PIPE);
	if (ch == '>' || ch == '<')
		return (REDIRECTION);
    return (ERROR);
}

/**
 * @brief			Construct the first token object (if any) of the line
 * 					passed to the function
 *
 * @param line		string to extract tokens from
 * @return t_token*	Token struct containing information about the first token
 * 					of the line
 */
t_token *get_next_token(char *line)
{
    char *token_string;
	t_token	*tok;
	enum e_token_type first;
	int i;

	if (!line)
		return (NULL);
	first = get_token_type(line[0]);
	i = 0;
	while (line[i] && get_token_type(line[i]) == first)
		i++;
    ft_printf("i: %d", i);
	tok = malloc(sizeof(t_token));
	token_string = ft_substr(line, 0, i);
	tok->contents = token_string;
	tok->next = NULL;
	return (tok);
}

t_token *preprocess_input(char *input)
{
    t_token *result;
    t_token *iterator;
    size_t offset;

    result = get_next_token(input);
    iterator = result;
    offset = ft_strlen(iterator->contents);
    while(iterator)
    {
        ft_printf("Ptr: %p, String: %s, Type: %d\n", iterator, iterator->contents, iterator->type);
        iterator->next = get_next_token(input + offset);
        offset += ft_strlen(iterator->contents);
        iterator = iterator->next;
    }
    return result;
}

/**
 * @brief Turn a string into a list of tokens
 * @param input - input string
 * @return Linked list of token nodes
 *
 * @note - We will perform env variable expansion, group single quote strings as one token
 * and combine double quote strings after expansion, split tokens such as "hello or |>
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
t_token *tokenize(char *input)
{
    t_token *cleaned_input;

    cleaned_input = preprocess_input(input);
    return 0;
}

