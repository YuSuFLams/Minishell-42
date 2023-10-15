/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:32:40 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/09 14:13:43 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*ft_lstnew(int content)
{
	t_list	*s;

	s = (t_list *)malloc(sizeof(t_list));
	if (!s)
		return (NULL);
	s->content = content;
	s->next = NULL;
	return (s);
}
