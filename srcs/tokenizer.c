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
	if (ch == '"')
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

t_bool is_valid_identifier(char ch)
{
	return (ft_isalpha(ch) || ch == '_' || ch == '\'' || ch == '"');
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
	tok = malloc(sizeof(t_token));
	first = get_token_type(line[0]);
	i = 1;
    if (first == VARIABLE)
    {
		if (!line[1] || !is_valid_identifier(line[1]))
			first = WORD;
		while (line[i] && get_token_type(line[i]) == WORD)
			i++;
	}
	else if (first == WORD || first == WHITESPACE)
	{
		while ( line[i] && get_token_type(line[i]) == first)
			i++;
	}
	else if (first == REDIRECTION && get_token_type(line[i]) == first)
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
        if (iterator->next) {
            iterator->next->prev = iterator;
            offset += ft_strlen(iterator->next->contents);
        }
        iterator = iterator->next;
    }
    return result;
}

/**
 * @brief Free the token list given to it fully
 * @param list linked list of tokens
 */
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

/**
 * @brief Merges adjacent words in the list
 * @param list linked list of tokens to be scanned and merged
 * @return list with merged adjacent words
 */
t_token *merge_words(t_token *list)
{
	t_token *iterator;
	t_token *new_item;

	iterator = list;
	while (iterator)
	{
		if (iterator->next && iterator->type == WORD && iterator->next->type == WORD)
		{
			new_item = malloc(sizeof(t_token));
			new_item->type = WORD;
			new_item->contents = ft_strjoin(iterator->contents, iterator->next->contents);
			if (iterator->prev) {
				iterator->prev->next = new_item;
				new_item->prev = iterator->prev;
			} else {
				list = new_item;
				new_item->prev = NULL;
			}
			if (iterator->next->next) {
				iterator->next->next->prev = new_item;
				new_item->next = iterator->next->next;
			}
			else
				new_item->next = NULL;
			iterator->next->next = NULL;
			clear_tokenlist(&iterator);
			iterator = new_item;
		}
		else
			iterator = iterator->next;
	}
	return (list);
}

/**
 * @brief Merge the list given to it into one big word token
 * @param quote linked list of tokens to be merged
 * @return the word token with the merged contents
 */
t_token *merge_quotation_tokens(t_token *quote)
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
 * @brief Collapse the quotations in the token list into word tokens
 * @param single boolean indicating type of quotation to collapse
 * @param list linked list of tokens we are operating on
 * @return linked list of tokens after the collapse of the desired quotations
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
        if (iterator)
            iterator->next = NULL;
        open_quote->prev = NULL;
        close_quote = open_quote->next;
        while (close_quote && close_quote->type != qtype)
            close_quote = close_quote->next;
        if (!close_quote) {
			clear_tokenlist(&list);
			list = malloc(sizeof(t_token));
			*list = (t_token){ERROR, "UNCLOSED QUOTATION", NULL, NULL};
			return (list);
		}
		remainder = close_quote->next;
        close_quote->next = NULL;
        if (remainder)
            remainder->prev = NULL;
        newtoken = merge_quotation_tokens(open_quote);
		if (!iterator)
		{
			list = newtoken;
			if (!remainder)
				return (list);
		}
        clear_tokenlist(&open_quote);
        if (iterator)
            iterator->next = newtoken;
        newtoken->prev = iterator;
        newtoken->next = remainder;
        if (remainder)
            remainder->prev = newtoken;
        if (!newtoken->prev)
            list = newtoken;
        iterator = remainder;
    }
    return list;
}

/**
 * @brief Prune whitespace out of the token list
 * @param list linked list of tokens
 * @return pruned list
 */
t_token *discard_whitespace(t_token *list) {
    t_token *iterator;
    t_token *temp;

    iterator = list;
    while (iterator)
    {
        if (iterator->type == WHITESPACE || !(iterator->contents) || !(*(iterator->contents)))
        {
            if (iterator->prev && iterator->next)
            {
                iterator->prev->next = iterator->next;
                iterator->next->prev = iterator->prev;
            }
            else if (iterator->prev)
                iterator->prev->next = NULL;
            else if (iterator->next)
                list = iterator->next;
            else
                list = NULL;
            temp = iterator->next;
            free(iterator->contents);
            free(iterator);
            iterator = temp;
        }
        else
            iterator = iterator->next;
    }
    return (list);
}

/**
 * @brief Expand all variable tokens and replace them with the respective word
 * @param list linked list of all tokens
 * @return list but with no variable tokens
 */
t_token *expand_variables(t_token *list) {
    t_token *iterator;

    iterator = list;
    while (iterator)
    {
        if (iterator->type == VARIABLE) {
            iterator->type = WORD;
            iterator->contents = expand(iterator->contents + 1);
        }
        iterator = iterator->next;
    }
    return list;
}

void print_tokens(t_token *list)
{
    ft_printf("HEAD\n");
    while (list)
    {
        ft_printf("TYPE: ");
        if (list->type == VARIABLE)
            ft_printf("VARIABLE, ");
        else if (list->type == WORD)
            ft_printf("WORD, ");
        else if (list->type == REDIRECTION)
            ft_printf("REDIRECTION, ");
        else if (list->type == PIPE)
            ft_printf("PIPE, ");
        else if (list->type == WHITESPACE)
            ft_printf("WHITESPACE, ");
        else if (list->type == SINGLE_QUOTE)
            ft_printf("SINGLE_QUOTE, ");
        else if (list->type == DOUBLE_QUOTE)
            ft_printf("DOUBLE_QUOTE, ");
		else if (list->type == ERROR)
			ft_printf("ERROR, ");
        ft_printf("CONTENTS: %s, PREV: %p, NEXT: %p\n", list->contents, list->prev, list->next);
        list = list->next;
    }
    ft_printf("TAIL\n");
}

t_token *discard_dollar(t_token *list)
{
	t_token *iterator;
	t_token *temp;

	iterator = list;
	while (iterator)
	{
		if (iterator->type == VARIABLE && !((iterator->contents)[1]))
		{
			if (iterator->prev && iterator->next)
			{
				iterator->prev->next = iterator->next;
				iterator->next->prev = iterator->prev;
			}
			else if (iterator->prev)
				iterator->prev->next = NULL;
			else if (iterator->next)
				list = iterator->next;
			else
				list = NULL;
			temp = iterator->next;
			free(iterator->contents);
			free(iterator);
			iterator = temp;
		}
		else
			iterator = iterator->next;
	}
	return (list);
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

	if (!input || !*input)
		return (NULL);
    list = preprocess_input(input);
	list = discard_dollar(list);
	// print_tokens(list);
	list = collapse_quotes(TRUE, list);
	// print_tokens(list);
	list = expand_variables(list);
	// print_tokens(list);
	list = collapse_quotes(FALSE, list);
	print_tokens(list);
	list = merge_words(list);
	list = discard_whitespace(list);
	print_tokens(list);

	return (list);
}

