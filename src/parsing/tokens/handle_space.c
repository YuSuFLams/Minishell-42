/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 23:52:42 by ssaadaou          #+#    #+#             */
/*   Updated: 2023/10/14 21:44:56 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_space(char c)
{
	if (c == '\t' || c == '\f' || c == '\v'
		|| c == '\n' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	is_escaped_char(char c)
{
	return (c == '\"' || c == '\\' || c == '$');
}
