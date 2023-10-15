/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_helper_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:29:13 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/14 21:31:46 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_quotes(t_list *cmds, char quote_type)
{
	t_list	*curr;
	int		count;

	curr = cmds;
	count = 0;
	while (curr) 
	{
		if (curr->cmd[0] == quote_type)
			count++;
		curr = curr->next;
	}
	return (count);
}

int	check_start_end(t_list *curr)
{
	t_list	*tmp;

	tmp = curr;
	if (tmp && (tmp->type == p_pipe || is_redirection(tmp->type) == 1))
		if (tmp->next == NULL)
			return (1);
	tmp = curr;
	if (tmp && tmp->type == p_pipe)
		if (tmp->prev == NULL)
			return (1);
	return (0);
}
