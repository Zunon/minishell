#include "../inc/minishell.h"

t_bool parse_redirection(t_token **tracer) {
	if (!(*tracer)->next || (*tracer)->next->type != WORD)
		return FALSE;
	*tracer = (*tracer)->next;
	return TRUE;
}

t_bool parse_redirection_list(t_token **tracer) {
	if (!parse_redirection(tracer))
		return FALSE;
	if ((*tracer)->next && (*tracer)->next->type == REDIRECTION) {
		*tracer = (*tracer)->next;
		return parse_redirection_list(tracer);
	}
	return TRUE;
}

t_bool parse_simple_command_element(t_token **tracer) {
	if ((*tracer)->type == REDIRECTION)
		return parse_redirection_list(tracer);
	if ((*tracer)->type == WORD)
		return TRUE;
	return FALSE;
}

t_bool parse_simple_command(t_token **tracer) {
	if (!parse_simple_command_element(tracer)) {
		return FALSE;
	}
	if ((*tracer)->next) {
		*tracer = (*tracer)->next;
		if (parse_simple_command(tracer))
			return TRUE;
		*tracer = (*tracer)->prev;
	}
	return TRUE;
}

t_bool parse_pipeline(t_token *list) {
	t_token *tracer;

	if (!list)
		return (TRUE);
	tracer = list;
	if (!parse_simple_command(&tracer))
		return FALSE;
	if (tracer->next && tracer->next->type == PIPE)
	{
		if (!(tracer->next->next))
			return FALSE;
		tracer = tracer->next->next;
		return parse_pipeline(tracer);
	}
	return TRUE;
}

t_command	*parse_input(const char *input)
{
	t_token *list;

	list = tokenize((char *)input);
	// print_tokens(list);
	if (!list || list->type == ERROR) {
		ft_printf("Token Error: %s\n", list->contents);
		return (NULL);
	} else if (!parse_pipeline(list)) {
		ft_printf("Parse Error!\n");
		return (NULL);
	}
	// ft_printf("Success!\n");
	return (token_to_cmd_converter(list));
}
