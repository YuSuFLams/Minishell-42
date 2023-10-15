/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 23:53:44 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/13 23:54:02 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == src)
		return (dest);
	i = -1;
	while (++i < n)
		*(char *)(dest + i) = *(char *)(src + i);
	return (dest);
}
