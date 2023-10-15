/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:28:44 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/19 17:28:52 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (*(to_find + j) == '\0')
		return (str);
	while (*(str + i) != '\0')
	{
		while (*(str + i + j) == *(to_find + j) && *(str + i + j) != '\0')
			j++;
		if (*(to_find + j) == '\0')
			return (str + i);
		i++;
		j = 0;
	}
	return (NULL);
}
