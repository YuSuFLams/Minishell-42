/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaadaou <ssaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 03:46:06 by ssaadaou          #+#    #+#             */
/*   Updated: 2023/10/10 22:31:18 by ssaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_single_quote(int *i, char *str)
{
	int		j;
	char	*content;

	j = (*i) + 1;
	while (str[j] && str[j] != '\'')
		j++;
	content = ft_substr(str, (*i) + 1, j - (*i) - 1);
	if (str[j] == '\'')
		j++;
	else
	{
		(*i) = j;
		return (NULL);
	}
	(*i) = j;
	return (content);
}

char	*handle_double_quote(t_shell *m_sh, int *i, char *str)
{
	int		j;
	char	*content;
	char	*joined;
	char	*tmp;

	j = (*i) + 1;
	content = ft_strdup(""); 
	joined = NULL;
	while (str[j] && str[j] != '\"')
	{
		if (str[j] == '\\')
			joined = handle_slash(&j, str);
		else if (str[j] == '$')
			joined = handle_dollar(m_sh, &j, str);
		else
			joined = handle_char(&j, str);
		tmp = content;
		content = ft_strjoin(content, joined);
		free(joined);
		free(tmp);
	}
	if (str[j] == '\"')
		j++;
	(*i) = j;
	return (content);
}

char	*handle_quotes(t_shell *cmd, int *i, char *str)
{
	if (str[*i] == '\'')
		return (handle_single_quote(i, str));
	else if (str[*i] == '\"')
		return (handle_double_quote(cmd, i, str));
	else
		return (NULL);
}
