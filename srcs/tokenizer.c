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
		return (SPACE);
	if (ch == '|')
		return (PIPE);
	if (ch == '>' || ch == '<')
		return (REDIRECTION);
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
	char first;
	int i;

	if (!line)
		return (NULL);
	first = line[0];
	i = 0;
	while (get_token_type(line[i]) == first)
		i++;
	tok = malloc(sizeof(t_token));
	token_string = ft_substr(line, 0, i);
	tok->contents = token_string;
	tok->next = NULL;
	return (tok);
}

t_list **preprocess_input(char *input)
{
    t_list *result;
	t_bool opened_quote = false;
    int i;

    i = 0;
    result = ft_lstnew(NULL);
    result.content = match_input(input);//cat Makefile > outfile | cat outfile | grep "hello    $USER"
	// cat, Makefile, >, outfile, |, cat, outfile, |, grep, ", hello,     , $USER, "
    while(nowhitespace[++i])
    {

    }
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
 *  - Construct tokens
 *  - Group together single-quoted strings
 *  - Expand any variables and replace the corresponding token
 *  - Group together double-quoted strings
 * - Return list
 */
t_token_node *tokenize(char *input)
{
    t_list **cleaned_input;

    cleaned_input = preprocess_input(input);
	// combine single quotes

	// <w 'cat'>, <w Makefile>, <rd >>, <w outfile>, <p>, <w cat>, <w outfile>, <p>, <w grep>, <dq>, <w hello>, <w     >, <var USER>, <dq>
	// expand
	// <w 'cat'>, <w Makefile>, <rd >>, <w outfile>, <p>, <w cat>, <w outfile>, <p>, <w grep>, <dq>, <w hello>, <w     >, <w rriyas>, <dq>
	// <w 'cat'>, <w Makefile>, <rd >>, <w outfile>, <p>, <w cat>, <w outfile>, <p>, <w grep>, <w:q 'hello    rriyas'>
}

