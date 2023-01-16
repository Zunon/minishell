/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:59:31 by kalmheir          #+#    #+#             */
/*   Updated: 2023/01/16 23:59:34 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_bool	parse_redirection(t_token **tracer)
{
	if (!(*tracer)->next || (*tracer)->next->type != WORD)
		return (FALSE);
	*tracer = (*tracer)->next;
	return (TRUE);
}

t_bool	parse_redirection_list(t_token **tracer)
{
	if (!parse_redirection(tracer))
		return (FALSE);
	if ((*tracer)->next && (*tracer)->next->type == REDIRECTION)
	{
		*tracer = (*tracer)->next;
		return (parse_redirection_list(tracer));
	}
	return (TRUE);
}

t_bool	parse_simple_command_element(t_token **tracer)
{
	if ((*tracer)->type == REDIRECTION)
		return (parse_redirection_list(tracer));
	if ((*tracer)->type == WORD)
		return (TRUE);
	return (FALSE);
}

t_bool	parse_simple_command(t_token **tracer)
{
	if (!parse_simple_command_element(tracer))
	{
		return (FALSE);
	}
	if ((*tracer)->next)
	{
		*tracer = (*tracer)->next;
		if (parse_simple_command(tracer))
			return (TRUE);
		*tracer = (*tracer)->prev;
	}
	return (TRUE);
}

t_bool	parse_pipeline(t_token *list)
{
	t_token	*tracer;

	if (!list)
		return (TRUE);
	tracer = list;
	if (!parse_simple_command(&tracer))
		return (FALSE);
	if (tracer->next && tracer->next->type == PIPE)
	{
		if (!(tracer->next->next))
			return (FALSE);
		tracer = tracer->next->next;
		return (parse_pipeline(tracer));
	}
	return (TRUE);
}
