/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:37:21 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/27 19:56:53 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_bool	check_redir_var(t_token *node, t_token **var)
{
	if (node->type != REDIRECTION || !ft_strncmp(node->contents, "<<", 2))
		return (FALSE);
	node = node->next;
	while (node->type == WHITESPACE && node->type != TAIL)
		node = node->next;
	if (node->type == VARIABLE)
	{
		*var = node;
		return (TRUE);
	}
	return (FALSE);
}

t_token	*first_ambiguous_redirect(t_token *list)
{
	char	**split;
	char	*value;
	size_t	split_len;
	t_token	*variable;

	split = NULL;
	split_len = 0;
	while (list && list->type != TAIL)
	{
		variable = NULL;
		if (check_redir_var(list, &variable))
		{
			value = expand(variable->contents + 1);
			split = ft_split(value, ' ');
			split_len = length_of_arr(split);
			freesplit(split);
			free(value);
			if (split_len > 1)
				return (list->next);
		}
		list = list->next;
	}
	return (NULL);
}

t_token	*go_to_adjacent_command(t_token *mid, t_bool go_right)
{
	enum e_token_type	end_type;

	if (go_right)
		end_type = TAIL;
	else
		end_type = HEAD;
	while (mid->type != end_type && mid->type != PIPE)
	{
		if (go_right)
			mid = mid->next;
		else
			mid = mid->prev;
	}
	return (mid);
}

void	splice_out_command(t_token *ambi)
{
	t_token	*left;
	t_token	*right;

	left = go_to_adjacent_command(ambi, FALSE);
	right = go_to_adjacent_command(ambi, TRUE);
	if (left->type == right->type
		|| (left->type == PIPE && right->type == TAIL))
		left = left->prev;
	else if (left->type == HEAD && right->type == PIPE)
		right = right->next;
	left->next->prev = NULL;
	right->prev->next = NULL;
	ambi = left->next;
	left->next = right;
	right->prev = left;
	clear_tokenlist(&ambi);
}

t_token	*throw_and_skip_pipe(t_token *list)
{
	t_token	*ambi;

	ambi = first_ambiguous_redirect(list);
	while (ambi)
	{
		fd_printf(STDERR_FILENO, "krsh: $%s: ambiguous redirect\n",
			ambi->contents);
		splice_out_command(ambi);
		ambi = first_ambiguous_redirect(list);
	}
	return (list);
}
