/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaadaou <ssaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 00:50:13 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/10 22:11:13 by ssaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_args_all(t_list *tmp)
{
	int	count_args;

	count_args = 0;
	while (tmp && tmp->type == word)
	{
		count_args++;
		tmp = tmp->next;
	}
	return (count_args);
}

int	dup_another_array(t_comd *curr, t_list **token, int count_args, int k)
{
	char	**new_args;
	int		j;
	t_list	*tmp;

	tmp = NULL;
	j = set_size_arg(curr->args);
	new_args = (char **)malloc((j + count_args + 1) * sizeof(char *));
	if (!new_args)
		return (0);
	while (++k < j)
		new_args[k] = curr->args[k];
	while (*token && (*token)->type == word)
	{
		new_args[j] = ft_strdup((*token)->cmd);
		free((*token)->cmd);
		if (new_args[j] == NULL)
			return (freesplit(new_args, 0), 0);
		j++;
		tmp = (*token);
		*token = (*token)->next;
		free(tmp);
	}
	return (new_args[j] = NULL, free(curr->args), curr->args = new_args, 0);
}

void	fill_args2(t_comd *curr, int count_args, t_list **token)
{
	t_list	*tmp1;
	int		i;

	tmp1 = NULL;
	i = 0;
	curr->args = (char **)malloc((count_args + 1) * sizeof(char *));
	if (!curr->args)
		return ;
	while (i < count_args)
	{
		if (*token && (*token)->type == word)
		{
			curr->args[i] = ft_strdup((*token)->cmd);
			free((*token)->cmd);
			if (curr->args[i] == NULL)
				return ;
			tmp1 = *token;
			*token = (*token)->next;
			free(tmp1);
		}
		else
			break ;
		i++;
	}
	curr->args[i] = NULL;
}

void	fill_args(t_comd *curr, t_list **token)
{
	int		count_args;
	t_list	*tmp;

	tmp = *token;
	count_args = count_args_all(tmp);
	if (!count_args)
		return ;
	if (curr->args)
		dup_another_array(curr, token, count_args, -1);
	else
		fill_args2(curr, count_args, token);
}

bool	parse_command(t_shell *m_sh, char *input, t_list **tokens, \
t_comd **parsed_cmd)
{
	if (tokenisation(m_sh, input, tokens) == 1)
	{
		clear_list(tokens);
		free(input);
		return (false);
	}
	if (syntax_error(*tokens) == 1)
	{
		g_exit_cmd = 258;
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		clear_list(tokens);
		free(input);
		return (false);
	}
	else
	{
		*parsed_cmd = init_cmds();
		handle_special_tokens(*parsed_cmd, tokens, m_sh, NULL);
		clear_list(tokens);
		free(input);
	}
	return (true);
}
