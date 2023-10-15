/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_helper_fct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:27:43 by ssaadaou          #+#    #+#             */
/*   Updated: 2023/10/13 04:00:23 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_slash(int *i, char *str)
{
	char	new[2];

	if (is_escaped_char(str[*i + 1]))
	{
		new[0] = str[*i + 1];
		*i += 2;
	}
	else
	{
		new[0] = '\\';
		(*i)++;
	}
	new[1] = '\0';
	return (ft_strdup(new));
}

char	*handle_char(int *i, char *str)
{
	char	ch;
	char	*s;

	ch = str[*i];
	*i += 1;
	s = (char *)malloc(2 * sizeof(char));
	if (!s)
		return (NULL);
	*s = ch;
	*(s + 1) = '\0';
	return (s);
}
