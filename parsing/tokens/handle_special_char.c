/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaadaou <ssaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 03:46:28 by ssaadaou          #+#    #+#             */
/*   Updated: 2023/10/10 22:38:24 by ssaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redirection(t_type token_type)
{
	return (token_type == input || token_type == output || \
		token_type == output_append || token_type == heredoc);
}

int	magic_character(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

void	handle_out_redirection(char *str, int *i, t_list **tokens)
{
	if (str[(*i) + 1] == '>')
	{
		add_back(tokens, ">>", output_append);
		(*i)++;
	}
	else
		add_back(tokens, ">", output);
}

void	handle_in_redirection(char *str, int *i, t_list **tokens)
{
	if (str[(*i) + 1] == '<')
	{
		add_back(tokens, "<<", heredoc);
		(*i)++;
	}
	else
		add_back(tokens, "<", input);
}

void	handle_magic_charc(int *i, char *str, t_list **tokens)
{
	if (str[*i] == '<')
		handle_in_redirection(str, i, tokens);
	else if (str[*i] == '>')
		handle_out_redirection(str, i, tokens);
	else if (str[*i] == '|')
		add_back(tokens, "|", p_pipe);
	(*i)++;
}
