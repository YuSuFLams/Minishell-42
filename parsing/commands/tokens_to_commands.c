/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 05:02:38 by ssaadaou          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_word_token(t_comd *command, t_list **tokens)
{
	fill_args(command, tokens);
}

void	handle_input_token(t_comd *command, t_list **tokens, t_list *tmp)
{
	handle_input_redirect(command, tokens);
	free(tmp->cmd);
	free(tmp);
}

void	handle_output_token(t_comd *command, t_list **tokens, t_list *tmp)
{
	handle_output_redirect(command, tokens);
	free(tmp->cmd);
	free(tmp);
}

void	handle_pipe_token(t_comd *command, t_list **tokens, t_shell *mini, \
t_list *tmp)
{
	handle_her_red(command, tokens, mini);
	free (tmp->cmd);
	free(tmp);
}

void	handle_special_tokens(t_comd *command, t_list **tokens, t_shell *mini, \
t_list *tmp)
{
	while (*tokens != NULL) 
	{
		tmp = *tokens;
		if ((*tokens)->type == word)
			handle_word_token(command, tokens);
		else if ((*tokens)->type == input)
			handle_input_token(command, tokens, tmp);
		else if ((*tokens)->type == output)
			handle_output_token(command, tokens, tmp);
		else if ((*tokens)->type == output_append)
			handle_append_token(command, tokens, tmp);
		else if ((*tokens)->type == p_pipe)
		{
			(*tokens) = (*tokens)->next;
			(free (tmp->cmd), free(tmp), init_new_cmd(&command));
		}
		else if ((*tokens)->type == heredoc)
			handle_pipe_token(command, tokens, mini, tmp);
		else
			*tokens = (*tokens)->next;
		if (g_exit_cmd == 1)
			return ;
	}
}
