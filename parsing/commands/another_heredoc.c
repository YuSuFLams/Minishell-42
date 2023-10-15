/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 04:25:05 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_input_redirect(t_comd *curr, t_list **token)
{
	t_list	*tmp;

	tmp = NULL;
	(*token) = (*token)->next;
	if (*token && (*token)->type == word)
	{
		tmp = *token;
		if (curr->input_redirect != -1)
		{
			curr->input_redirect = open((*token)->cmd, O_RDONLY);
			if (curr->input_redirect == -1)
			{
				perror("error opening file input");
				g_exit_cmd = 1;
				return ;
			}
			free((*token)->cmd);
		}
		(*token) = (*token)->next;
		free(tmp);
	}
}

void	handle_output_redirect(t_comd *curr, t_list **token)
{
	t_list	*tmp;

	tmp = NULL;
	(*token) = (*token)->next;
	if (*token && (*token)->type == word)
	{
		if (curr->output_redirect != -1)
		{
			if (curr->output_redirect != 1)
				close(curr->output_redirect);
			curr->output_redirect = open((*token)->cmd, O_WRONLY | O_CREAT \
			| O_TRUNC, 0644);
			if (curr->output_redirect == -1)
			{
				perror("error opening file output");
				g_exit_cmd = 1;
				return ;
			}
			free((*token)->cmd);
		}
		tmp = *token;
		(*token) = (*token)->next;
		free(tmp);
	}
}

void	handle_output_append(t_comd *curr, t_list **token)
{
	t_list	*tmp;

	tmp = NULL;
	(*token) = (*token)->next;
	if (*token && (*token)->type == word)
	{
		if (curr->output_redirect != -1)
		{
			curr->output_redirect = open((*token)->cmd, O_WRONLY | O_CREAT \
			| O_APPEND, 0666);
			if (curr->output_redirect == -1)
			{
				perror("error opening file input");
				g_exit_cmd = 1;
				return ;
			}
			free((*token)->cmd);
		}
		tmp = *token;
		(*token) = (*token)->next;
		free(tmp);
	}
}

void	handle_her_red(t_comd *curr, t_list **token, t_shell *mini)
{
	t_list	*tmp;

	tmp = NULL;
	(*token) = (*token)->next;
	if (*token && (*token)->type == word)
	{
		curr->input_redirect = heredoc_case(*token, mini);
		if (curr->input_redirect == -1)
		{
			perror("error opening file");
			g_exit_cmd = 1;
			return ;
		}
		tmp = *token;
		(*token) = (*token)->next;
		free(tmp);
	}
}

void	handle_append_token(t_comd *command, t_list **tokens, t_list *tmp)
{
	handle_output_append(command, tokens);
	free(tmp->cmd);
	free(tmp);
}
