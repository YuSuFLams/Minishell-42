/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaadaou <ssaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 20:57:14 by ssaadaou          #+#    #+#             */
/*   Updated: 2023/10/10 22:36:13 by ssaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	extract_word(int start, int i, char *str, t_list **tokens)
{
	char	*substr;

	if (i > start && str[i] != '\'')
	{
		substr = ft_substr(str, start, i - start);
		add_back(tokens, substr, word);
		free(substr);
	}
}

char	*extract_var_content(t_shell *m_sh, int *j, char *str)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *j;
	while (str[*j] && str[*j] != '\"' &&!is_space(str[*j]) && \
	!magic_character(str[*j]) && str[*j] != '\'' )
		(*j)++;
	var_name = ft_substr(str, start, *j - start);
	var_value = expander_cmd(var_name, m_sh); 
	return (var_value); 
}

char	*handle_dollar(t_shell *m_sh, int *i, char *str)
{
	char	*var_content;

	var_content = extract_var_content(m_sh, i, str);
	while (is_var_char(str[(*i)])) 
		(*i)++;
	return (var_content);
}

void	handle_word(t_shell *m_sh, int *i, char *str, t_list **tokens)
{
	char	*curr_word;
	char	*joined;
	char	*tmp;

	curr_word = ft_strdup("");
	joined = NULL;
	while (str[*i] && !is_space(str[*i]) && !magic_character(str[*i]))
	{
		if (quotes(str[*i]))
			joined = handle_quotes(m_sh, i, str);
		else if (str[*i] == '\\')
			joined = handle_slash(i, str);
		else if (str[*i] == '$')
			joined = handle_dollar(m_sh, i, str);
		else
			joined = handle_char(i, str);
		tmp = curr_word;
		curr_word = ft_strjoin(curr_word, joined);
		if (!joined)
			return ;
		free(tmp);
		free(joined);
	}
	add_back(tokens, curr_word, word);
	free(curr_word);
}

int	tokenisation(t_shell *m_sh, char *input, t_list **tokens)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (is_space(input[i]))
			handle_spc(&i, input);
		else if (magic_character(input[i]))
			handle_magic_charc(&i, input, tokens);
		else
			handle_word(m_sh, &i, input, tokens);
	}
	return (0);
}
