#include "../inc/minishell.h"

t_command   *parse_input(const char *input)
{
    t_token_node *list;

    list = tokenize(input);
    // @TODO: Recursive Descent Parsing Using our Grammar rules
}

