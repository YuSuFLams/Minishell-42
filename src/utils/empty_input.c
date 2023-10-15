/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 00:10:16 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/29 03:07:15 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	empty_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i] != '\0')
		if (!is_space(line[i]))
			return (false);
	return (true);
}
