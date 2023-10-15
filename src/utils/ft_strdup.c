/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:43:29 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/21 22:49:55 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(ft_strlen(s) + 1 * sizeof(char));
	if (!str)
		return (str);
	i = -1;
	while (*(s + (++i)))
		*(str + i) = *(s + i);
	*(str + i) = '\0';
	return (str);
}
