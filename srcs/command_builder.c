/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:30:54 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/14 21:03:14 by rriyas           ###   ########.fr       */
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
	return (NULL);
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
	return (NULL);
}

t_token *get_next_cmd(t_token *list)
{
	return (NULL);
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
	return (NULL);
}