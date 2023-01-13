#include "../inc/minishell.h"

char *match_input(char *string)
{
    char *result;


}

t_list **preprocess_input(char *input)
{
    t_list *result;
    char **nowhitespace;
    int i;

    i = 0;
    nowhitespace = ft_split(input, ' ');
    result = ft_lstnew(NULL);
    result.content = match_input(nowhitespace[0])
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
}

