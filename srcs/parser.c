#include "../inc/minishell.h"

t_command   *parse_input(const char *input)
{
    t_token *list;

    list = tokenize((char *)input);
    // @TODO: Recursive Descent Parsing Using our Grammar rules
    return (0);
}

