/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:15:43 by ssaadaou          #+#    #+#             */
/*   Updated: 2023/10/13 05:07:36 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*create_list_node(char *cmd, t_type type)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->cmd = ft_strdup(cmd);
	node->type = type;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back(t_list **head, char *cmd, t_type type)
{
	t_list	*tmp;
	t_list	*node;

	node = create_list_node(cmd, type);
	tmp = *head;
	if (!(*head))
	{
		*head = node;
		(*head)->next = NULL;
		(*head)->prev = NULL;
		return ;
	}
	tmp = ft_lstlast(*head);
	tmp->next = node;
	tmp->next->prev = tmp;
}
