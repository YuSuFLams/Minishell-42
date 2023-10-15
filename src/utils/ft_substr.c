/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:41:20 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/09 14:14:28 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = (char *)malloc(len + 1 * sizeof(char));
	if (!str)
		return (str);
	i = -1;
	while (++i < len && s[i + start] && start < ft_strlen(s))
		*(str + i) = *(s + (i + start));
	*(str + i) = '\0';
	return (str);
}
