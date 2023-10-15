/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_creat_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 01:06:57 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:04:53 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	split_env_line(char *str, char **key, char **value)
{
	int	pos;

	if (!ft_strchr(str, '='))
	{
		*key = NULL;
		*value = NULL;
		return ;
	}
	pos = ft_strchr(str, '=') - str;
	*key = ft_strndup(str, pos);
	*value = ft_strdup(str + pos + 1);
}
