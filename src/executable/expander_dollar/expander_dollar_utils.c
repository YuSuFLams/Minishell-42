/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaadaou <ssaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 01:12:43 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/10 00:09:23 by ssaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*join_char(char c)
{
	char	*s;

	s = malloc(sizeof(char) * 2);
	if (!s)
		return (NULL);
	*s = c;
	*(s + 1) = '\0';
	return (s);
}

int	check_int_after_dol(char *s, int pos)
{
	int	i;

	i = pos;
	if (*(s + pos) == '$')
		if (ft_isdigit(*(s + pos + 1)))
			pos += 2;
	return (pos - i);
}

bool	aftre_do(int c)
{
	if (!c)
		return (false);
	if (c == '$' || c == '?' || c == '_')
		return (true);
	return (false);
}

bool	aftre_do_1(char *s, int i)
{
	if (s[i] == '$' && s[i + 1] && (s[i + 1] != ' ' && s[i + 1] != '~'\
	&& (s[i + 1] != '"' || s[i + 2])))
		return (true);
	return (false);
}

char	*strjoin_another(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}
