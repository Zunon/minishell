/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:23:17 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/19 19:23:17 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	get_pipeline_size(t_command *cmd)
{
	t_command	*iterator;
	int			i;

	i = 0;
	iterator = cmd;
	while (iterator)
	{
		i++;
		iterator = iterator->next;
	}
	return (i);
}

static void	free_cmdnode(t_command *cmd, t_command *pipeline)
{
	t_command	*temp;

	temp = pipeline;
	while (temp && temp->next != cmd)
		temp = temp->next;
	free(cmd);
	temp->next = NULL;
}

static t_token	*get_next_cmd(t_token *list)
{
	while (list && list->type != PIPE)
		list = list->next;
	if (list && list->type == PIPE)
		list = list->next;
	return (list);
}

static void	construct_command(int *i, t_token **iterator, t_command **cmd)
{
	(*cmd)->id = *i;
	(*cmd)->redirects = extract_redirects((*iterator));
	(*cmd)->words = extract_words((*iterator));
	(*iterator) = get_next_cmd((*iterator));
	(*cmd)->next = malloc(sizeof(t_command));
	(*cmd) = (*cmd)->next;
	*i = *i + 1;
}

t_command	*conv_tok_to_cmd(t_token *list)
{
	t_token		*iterator;
	t_command	*cmd;
	t_command	*pipeline;
	int			i;

	if (!list)
		return (NULL);
	i = 0;
	iterator = list;
	cmd = ft_calloc(1, sizeof(t_command));
	pipeline = cmd;
	while (iterator)
		construct_command(&i, &iterator, &cmd);
	if (cmd == pipeline)
	{
		free(pipeline);
		pipeline = NULL;
		clear_tokenlist(&list);
		return (pipeline);
	}
	clear_tokenlist(&list);
	free_cmdnode(cmd, pipeline);
	g_krsh.num_of_cmds = get_pipeline_size(pipeline);
	return (pipeline);
}
