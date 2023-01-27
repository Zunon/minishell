/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_funcs0.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:47:35 by kalmheir          #+#    #+#             */
/*   Updated: 2022/06/26 15:17:47 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft.h"

/**
 * @brief Attaches a node to become the new tail.
 * This is done by iterating through the given linked list and attaches the
 * passed node to become the new tail.
 * @param lst	List to add onto.
 * @param new	Node to attach.
*/
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->next = 0;
		return ;
	}
	ft_lstlast(*lst)->next = new;
}

/**
 * @brief Applies a function to each node in the list.
 * Applies anonymous function f to each content member of the nodes in the
 * linked list.
 * @param lst	List to iterate on.
 * @param f		Function to apply on each content.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst->next)
	{
		f(lst->content);
		lst = lst->next;
	}
	f(lst->content);
}

/**
 * @brief Creates a new list based on a mapping function and a passed list.
 * Allocates a new linked list and inserts nodes based on the output of f.
 * @param lst	List to be mapped from.
 * @param f		Function to apply to map.
 * @param del	Function to cleanly delete content.
 * @return Newly mapped list.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*old;
	t_list	*result;

	old = lst;
	if (!lst)
		return (0);
	result = ft_lstnew((*f)(lst->content));
	if (lst->next)
		lst = lst->next;
	while (lst->next)
	{
		ft_lstadd_back(&result, ft_lstnew((*f)(lst->content)));
		lst = lst->next;
	}
	ft_lstadd_back(&result, ft_lstnew((*f)(lst->content)));
	ft_lstclear(&old, del);
	return (result);
}

/**
 * @brief Allocates and returns a new node with given content.
 *
 * @param content	Content to be attached to node.
 * @return Newly allocated node.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*result;

	result = ft_calloc(1, sizeof(t_list));
	if (!result)
		return (0);
	result->content = content;
	result->next = 0;
	return (result);
}

/**
 * @brief Counts the number of nodes in the given list.
 *
 * @param lst	List to iterate through.
 * @return Number of nodes in the list.
 */
int	ft_lstsize(t_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
