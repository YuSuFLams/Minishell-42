/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:34:51 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/09 14:13:34 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new_cmd)
{
	t_list	*cmd;

	cmd = *lst;
	if (!new_cmd)
		return ;
	if (!(*lst))
	{
		*lst = new_cmd;
		return ;
	}
	cmd = ft_lstlast(*lst);
	cmd->next = new_cmd;
}
