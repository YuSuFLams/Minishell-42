/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_all_digit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:55:52 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/13 06:21:39 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_all_digit(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (*(s + i) && is_space(*(s + i)))
		i++;
	while (*(s + i))
	{
		if (!ft_isdigit(*(s + i)))
			return (0);
		i++;
	}
	return (1);
}
