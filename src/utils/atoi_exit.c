/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:03:42 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/14 03:46:57 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

long long int	atoi_exit(const char *str)
{
	long long int	n;
	int				sign;

	n = 0;
	sign = 1;
	if (!ft_strcmp((char *)str, "-9223372036854775808"))
		return (LLONG_MIN);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		if (n > (LLONG_MAX - (*str - '0')) / 10)
			errno = ERANGE;
		n = n * 10 + (*str++ - '0');
	}
	return (n * sign);
}
