/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 01:23:36 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/16 01:23:54 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if ((unsigned char )c == 0)
		return ((char *)s + ft_strlen(s));
	i = -1;
	while (*(s + (++i)))
		if (*(s + i) == (unsigned char )c)
			return ((char *)(s + i));
	return (NULL);
}
