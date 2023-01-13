/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs_desc_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:30:54 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/14 00:34:16 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// t_command *token_to_cmd_converter(t_token *list)
// {
// 	t_command *cmd;
// 	int i;

// 	if (!list)
// 		return (NULL);
// 	i = 0;
// 	while (list)
// 	{
// 		cmd = malloc(sizeof(t_command));
// 		cmd->id = i;
// 		cmd->words
// 		list = list->next;
// 	}
// }


t_bool _WORD(t_token *tok)
{
	ft_printf("WORD: %d\n", tok->type);
	return (tok->type == WORD);
}

t_bool _REDIRECTION(t_token *tok)
{
	if (!tok->next)
		return (FALSE);
	ft_printf("REDIRECTION: %d\n", tok->type);
	return (tok->type == REDIRECTION && tok->next->type == WORD);
}



t_bool REDIRECTION_LIST(t_token *tok)
{
	if (!tok)
		return (TRUE);
	ft_printf("REDIRECTION LIST: %d\n", tok->type);
	if (tok->next && tok->next->next && _REDIRECTION(tok) && REDIRECTION_LIST(tok->next->next))
		return (TRUE);
	return (_REDIRECTION(tok));
}

t_bool SIMPLE_COMMAND_ELEMENT(t_token *tok)
{
	ft_printf("SIMPLE_COMMAND_ELEMENT: %d\n", tok->type);

	return (REDIRECTION_LIST(tok) || _WORD(tok));
}
t_bool SIMPLE_COMMAND(t_token *tok)
{
	if (!tok)
		return (TRUE);
	ft_printf("SIMPLE_COMMAND: %d\n", tok->type);
	if (tok->next && SIMPLE_COMMAND_ELEMENT(tok) && SIMPLE_COMMAND(tok->next))
		return (TRUE);
	return (SIMPLE_COMMAND_ELEMENT(tok));
}

t_bool PIPELINE(t_token *tok)
{
	if (!tok)
		return (TRUE);
	ft_printf("PIPELINE: %d\n", tok->type);
	if (tok->next && SIMPLE_COMMAND(tok) && tok->next->type == PIPE && PIPELINE(tok->next->next))
		return (TRUE);
	// write(1, "sup", 3);
	return (SIMPLE_COMMAND(tok));
}

t_command *recurs_desc_parser(t_token *list)
{
	t_command *pipeline;
	t_token *ptr;

	ptr = list;
	list = malloc(sizeof(t_token));
	list->contents = ft_strdup("cat");
	list->type = WORD;

	list->next = malloc(sizeof(t_token));
	list->next->contents = ft_strdup("Makefile");
	list->next->type = WORD;

	list->next->next = malloc(sizeof(t_token));
	list->next->next->contents = ft_strdup(">");
	list->next->next->type = REDIRECTION;
	list->next->next->next = NULL;
	if (PIPELINE(list) == TRUE)
		write(1, "WORKS", 5);
	// if (!PIPELINE(list))
	// 	return (NULL);
	// pipeline = token_to_cmd_converter(list);
	return (pipeline);
}
