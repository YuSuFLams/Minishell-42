/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaadaou <ssaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 23:52:42 by ssaadaou          #+#    #+#             */
/*   Updated: 2023/10/15 03:17:00 by ssaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_spc(int *i, char *str)
{
	while (str[*i] && is_space(str[*i]))
		(*i)++;
}

int	quotes(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}
