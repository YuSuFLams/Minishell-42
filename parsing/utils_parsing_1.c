/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:02:49 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/14 20:04:27 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_comd	*init_cmds(void)
{
	t_comd	*new_cmd;

	new_cmd = malloc(sizeof(t_comd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = NULL;
	new_cmd->input_redirect = 0;
	new_cmd->output_redirect = 1;
	new_cmd->heredoc_fd = 0;
	new_cmd->append = 1;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
}

void	clear_list(t_list **head)
{
	t_list	*tmp;

	if (!head || !(*head))
		return ;
	while (*head)
	{
		if ((*head)->cmd)
			free((*head)->cmd);
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
	free(*head);
}
