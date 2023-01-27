/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_funcs1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:50:07 by kalmheir          #+#    #+#             */
/*   Updated: 2022/06/26 15:24:29 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft.h"

/**
 * @brief Finds the tail of the given list.
 *
 * @param lst	List to be iterated through.
 * @return The ultimate node within the list.
 */
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/**
 * @brief Unallocates given node.
 * Uses the given anonymous function del that is supposed to unallocate the
 * content where applicable.
 * @param lst	Node to be freed
 * @param del	Function to free the content of the node
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (del)
		(*del)(lst->content);
	free(lst);
}

/**
 * @brief Unallocates the entire list given.
 * Iterates through the entire list freeing every node using ft_lstdelone().
 * @param lst	List to be freed
 * @param del	Function to free the content of a given node.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*holder;

	if (!lst || !*lst || !del)
		return ;
	while ((*lst)->next)
	{
		holder = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = holder;
	}
	ft_lstdelone(*lst, del);
	*lst = 0;
}

/**
 * @brief Attaches a node to become the new head.
 *
 * @param lst List to be attached to.
 * @param new New head of the list.
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	new->next = *lst;
	*lst = new;
}
