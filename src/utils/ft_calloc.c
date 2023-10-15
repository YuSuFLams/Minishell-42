/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:25:20 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/09 14:13:23 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;

	i = -1;
	while (++i < n)
		*(unsigned char *)(s + i) = (unsigned char)c;
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = malloc(count * size);
	if (!str)
		return (str);
	ft_bzero(str, (count * size));
	return (str);
}
