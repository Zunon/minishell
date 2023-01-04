/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:04:06 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/04 22:08:15 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief			Function to deallocate memory for the linked list of redirections
 * 					belongin to any command
 *
 * @param redir		Linked list of redirections for the command
 */
void free_redirects(t_redirect *redir)
{
	t_redirect *temp;

	if (!redir)
		return;
	while (redir)
	{
		temp = redir;
		redir = redir->next;
		free(temp->here_doc_delim);
		free(temp->redirectee.word);
		free(temp);
	}
}

/**
 * @brief			Function to deallocate memory for any linked list of words
 *
 * @param word_list	List to clear
 */
void free_word_list(t_word_list *word_list)
{
	t_word_list *temp;

	if (!word_list)
		return;
	while (word_list)
	{
		temp = word_list;
		word_list = word_list->next;
		free(temp->word->word);
		free(temp->word);
		free(temp);
	}
}

/**
 * @brief			Function to deallocate memory for a linked list of commands in a pipeline
 *
 * @param cmd		Linked list of commands
 */
void free_commands(t_command *cmd)
{
	t_command *temp;

	if (!cmd)
		return;
	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		free_redirects(temp->redirects);
		free_word_list(temp->words);
		free(temp);
	}
}
