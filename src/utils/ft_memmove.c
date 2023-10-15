/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 23:49:58 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/13 23:50:16 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == src)
		return (dest);
	if (dest > src)
		while (n--)
			*(char *)(dest + n) = *(char *)(src + n);
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
