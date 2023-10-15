/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:02:37 by ssaadaou          #+#    #+#             */
/*   Updated: 2023/10/13 03:29:56 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_var_char(char c)
{
	return (c == '$' || c == '_');
}

int	skip_escape(int j, char *str)
{
	if (str[j] == '\\' && (str[j + 1] == '\"' || str[j + 1] == '\\' \
	|| str[j + 1] == '$'))
		return (j + 1);
	return (j);
}

char	*extract_string(int start, int j, char *str)
{
	char	*substr;

	substr = NULL;
	if (j > start)
		substr = ft_substr(str, start, j - start);
	return (substr);
}

int	extract_var(int j, char *str)
{
	j++;
	while (is_var_char(str[j]))
		j++;
	return (j);
}

int	extract_normal_char(char *str, int j)
{
	while (str[j] && str[j] != '\"' && str[j] != '\\' && str[j] != '$')
		j++;
	return (j);
}
