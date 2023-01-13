/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs_desc_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:30:54 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/13 22:48:16 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_command *token_to_cmd_converter(t_token *list)
{
	t_command *cmd;
	int i;

	if (!list)
		return (NULL);
	i = 0;
	while (list)
	{
		cmd = malloc(sizeof(t_command));
		cmd->id = i;
		cmd->
		list = list->next;
	}

}

t_command *recurs_desc_parser(t_token *list)
{
	t_command *pipeline;

	if (!PIPELINE(list))
		return (NULL);
	pipeline = token_to_cmd_converter(list);
	return (pipeline);
}

t_bool PIPELINE(t_token *tok)
{
	return (SIMPLE_COMMAND(tok) || (SIMPLE_COMMAND(tok) && PIPELINE(tok->next)));
}

t_bool SIMPLE_COMMAND(t_token *tok)
{
	return (SIMPLE_COMMAND_ELEMENT(tok) || (SIMPLE_COMMAND_ELEMENT(tok) && SIMPLE_COMMAND(tok->next)));
}

t_bool SIMPLE_COMMAND_ELEMENT(t_token *tok)
{
	return (WORD(tok) || REDIRECTION_LIST(tok));
}

t_bool REDIRECTION_LIST(t_token *tok)
{
	return (REDIRECTION(tok) || (REDIRECTION(tok) && REDIRECTION(tok->next)));
}

t_bool WORD(t_token *tok)
{
	return (tok->type == WORD);
}

t_bool REDIRECTION(t_token *tok)
{
	return (tok->type == REDIRECTION);
}