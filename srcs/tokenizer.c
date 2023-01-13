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
	if (ft_iswhitespace(ch))
		return (WHITESPACE);
	if (ch == '|')
		return (PIPE);
	if (ch == '>' || ch == '<')
		return (REDIRECTION);
    return (WORD);
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

	if (!line || !*line)
		return (NULL);
	first = get_token_type(line[0]);
	i = 0;
	while ( line[i] && get_token_type(line[i]) == first)
		i++;
	tok = malloc(sizeof(t_token));
	token_string = ft_substr(line, 0, i);
    *tok = (t_token){first, token_string, NULL, NULL};
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
        iterator->next = get_next_token(input + offset);
        if (iterator->next)
            iterator->next->prev = iterator;
        offset += ft_strlen(iterator->contents);
        iterator = iterator->next;
    }
    return result;
}

void clear_tokenlist(t_token **list)
{
    t_token	*holder;

    if (!list || !*list)
        return ;
    while (*list)
    {
        holder = (*list)->next;
        free((*list)->contents);
        free(*list);
        *list = holder;
    }
    list = NULL;
}

t_token *merge_word(t_token *quote)
{
    char *final_content;
    enum e_token_type type;
    t_token *iterator;
    t_token *result;

    final_content = ft_calloc(1, 1);
    type = quote->type;
    iterator = quote->next;
    while (iterator->type != type)
    {
        final_content = ft_strjoin(final_content, iterator->contents);
        iterator = iterator->next;
    }
    result = malloc(sizeof(t_token));
    *result = (t_token){WORD, final_content};
    return (result);
}

/**
 * @TODO:
 * @param list
 * @return
 */
t_token *collapse_quotes(t_bool single, t_token *list) {
    t_token *iterator;
    t_token *open_quote;
    t_token *close_quote;
    t_token *remainder;
    t_token *newtoken;
    enum e_token_type qtype;
    enum e_token_type otype;
    t_bool enclosed;

    if (single)
    {
        qtype = SINGLE_QUOTE;
        otype = DOUBLE_QUOTE;
    }
    else
    {
        qtype = DOUBLE_QUOTE;
        otype = SINGLE_QUOTE;
    }
    iterator = list;
    enclosed = FALSE;
    while (iterator)
    {
        // find open quote, null its prev and its prev's next:
        while (iterator && (iterator->type != qtype || enclosed))
        {
            if (iterator->type == otype)
                enclosed = !enclosed;
            iterator = iterator->next;
        }
        if (!iterator)
            return (list);
        open_quote = iterator;
        iterator = open_quote->prev;
        iterator->next = NULL;
        open_quote->prev = NULL;
        // find closed quote, null its next and its next's prev:
        close_quote = open_quote->next;
        while (close_quote && close_quote->type != qtype)
            close_quote = close_quote->next;
        if (!close_quote)
            return (NULL); // NULL on error (unclosed quote)
        remainder = close_quote->next;
        close_quote->next = NULL;
        remainder->prev = NULL;
        // merge everything between
        newtoken = merge_word(open_quote);
        clear_tokenlist(open_quote);
        // do surgery on list with new node
        iterator->next = newtoken;
        newtoken->prev = iterator;
        newtoken->next = remainder;
        remainder->prev = newtoken;
    }
    return list;
}

/**
 *
 * @param list
 * @return
 */
t_token *expand_variables(t_token *list)
{
    expan
    return list;
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
    t_token *list;

    list = preprocess_input(input);
    list = collapse_quotes(TRUE, list);
    list = expand_variables(list);
    list = collapse_quotes(FALSE, list);
    return (list);
}

