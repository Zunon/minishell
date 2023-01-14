/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs_desc_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:30:54 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/14 16:13:52 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


enum e_direction get_direction(char *direction)
{
	if (ft_strncmp(">>", direction, 3))
		return (OUTPUT_APPEND);
	if (ft_strncmp("<<", direction, 3))
		return (HERE_DOC);
	if (ft_strncmp(">", direction, 2))
		return (OUTPUT);
	return (INPUT);
}

t_redirect *extract_redirects(t_token *list)
{
	// t_redirect *redirs;
	// t_redirect *iterator;
	// t_redirect *temp;

	// if (!list)
	// 	return (NULL);
	// redirs = malloc(sizeof(t_redirect));
	// iterator = redirs;
	// while (list && list->type != PIPE)
	// {
	// 	if (list->type == REDIRECTION)
	// 	{
	// 		iterator->redirectee = list->next->contents;
	// 		iterator->direction = get_direction(list->contents);
	// 		iterator->next = malloc(sizeof(t_redirect));
	// 		iterator = iterator->next;
	// 		list = list->next;
	// 	}
	// 	list = list->next;
	// }
	// if (iterator == redirs)
	// {
	// 	free(redirs);
	// 	redirs = NULL;
	// 	return redirs;
	// }
	// temp = redirs;
	// while (temp->next != iterator)
	// 	temp = temp->next;
	// free(iterator);
	// temp->next = NULL;
	// return (redirs);
}

t_list *extract_words(t_token *list)
{
	// t_list *words;
	// t_list *iterator;
	// t_list *temp;

	// if (!list)
	// 	return (NULL);
	// words = malloc(sizeof(t_list));
	// iterator = words;
	// while(list && list->type != PIPE)
	// {
	// 	if (list->type == WORD && list->prev && list->prev != REDIRECTION)
	// 	{
	// 		ft_lstadd_back(&words, ft_strdup(list->contents));
	// 		iterator->next = malloc(sizeof(t_list));
	// 		iterator = iterator->next;
	// 	}
	// 	list = list->next;
	// }
	// if (iterator == words)
	// {
	// 	ft_lstdelone(&words, free);
	// 	return (NULL);
	// }
	// temp = words;
	// while (temp)
	// {
	// 	if (!temp->content)
	// 		ft_lstdelone
	// 	temp = temp->next;
	// }
}

t_token *get_next_cmd(t_token *list)
{
}

// more thtan 2 < or >, ||
// variable expansions - first char after dollar sign should be underscore or alpha
// each quote should be each its own individial token
// doolar sign next chraif not valid - then WORD U $
// dollar sign then double quotes then name -
// dollar sign then single quotes then name -

t_command *token_to_cmd_converter(t_token *list)
{
	t_token *iterator;
	t_command *cmd;
	int i;

	if (!list)
		return (NULL);
	i = 0;
	iterator = list;
	while (iterator)
	{
		cmd = malloc(sizeof(t_command));
		cmd->id = i;
		cmd->redirects = extract_redirects(list);
		cmd->words = extract_words(list);
		iterator = get_next_cmd(iterator);
	}
}

t_bool _WORD(t_token *tok)
{
	//	ft_printf("WORD: %d\n", tok->type);
	return (tok->type == WORD);
}

t_bool _REDIRECTION(t_token *tok)
{
	if (!tok->next)
		return (FALSE);
	//	ft_printf("REDIRECTION: %d\n", tok->type);
	return (tok->type == REDIRECTION && tok->next->type == WORD);
}

t_bool REDIRECTION_LIST(t_token *tok)
{
	if (!tok)
		return (TRUE);
	ft_printf("REDIRECTION LIST: %d\n", tok->type);
	if (_REDIRECTION(tok) && tok->next && REDIRECTION_LIST(tok->next->next))
		return (TRUE);
	return (_REDIRECTION(tok));
}

t_bool SIMPLE_COMMAND_ELEMENT(t_token *tok)
{
	//	ft_printf("SIMPLE_COMMAND_ELEMENT: %d\n", tok->type);

	return (REDIRECTION_LIST(tok) || _WORD(tok));
}
t_bool SIMPLE_COMMAND(t_token *tok)
{
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
	if (tok->next && SIMPLE_COMMAND(tok) && PIPELINE(tok->next->next))
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
	//	if (PIPELINE(list) == TRUE)
	//		write(1, "WORKS", 5);
	// if (!PIPELINE(list))
	// 	return (NULL);
	// pipeline = token_to_cmd_converter(list);
	return (pipeline);
}
