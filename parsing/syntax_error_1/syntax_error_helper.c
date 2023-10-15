/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaadaou <ssaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 04:14:41 by ssaadaou          #+#    #+#             */
/*   Updated: 2023/10/10 22:09:55 by ssaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	first_check(t_list *curr)
{
	t_list	*tmp;

	tmp = curr;
	if (tmp->prev->type == word || tmp->prev->type == s_quote \
	|| tmp->prev->type == d_quote || tmp->prev->type == VAR)
		return (0);
	return (1);
}

int	pipe_error(t_list *curr)
{
	t_list	*tmp;

	tmp = curr;
	if (tmp->next && tmp->next->type == p_pipe)
		return (1);
	return (0);
}

int	redirection_error(t_list *curr)
{
	t_list	*tmp;

	tmp = curr;
	if (tmp->next && (tmp->next->type == word || tmp->next->type == d_quote \
	||tmp->next->type == s_quote))
		return (0);
	else
		return (1);
	return (0);
}

int	unmatched_quotes(t_list *cmds)
{
	int	s_quote;
	int	d_quote;

	s_quote = count_quotes(cmds, '\'');
	d_quote = count_quotes(cmds, '\"');
	if ((s_quote % 2) || (d_quote % 2))
		return (0);
	return (1);
}

int	syntax_error(t_list *cmds)
{
	t_list	*curr;

	curr = cmds;
	while (curr)
	{
		if (curr->type == p_pipe || is_redirection(curr->type) == 1)
		{
			if (check_start_end(curr))
				return (1);
		}
		if (curr->type == p_pipe)
			if (first_check (curr) || pipe_error(curr))
				return (1);
		if (is_redirection(curr->type) && redirection_error(curr))
			return (1);
		curr = curr->next;
	}
	return (0);
}
