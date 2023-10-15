/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:44:41 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/29 20:44:59 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (*(dest + i))
		i++;
	j = -1;
	while (*(src + (++j)))
		*(dest + i + j) = *(src + j);
	*(dest + i + j) = '\0';
	return (dest);
}
