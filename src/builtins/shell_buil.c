/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_buil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 02:06:11 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/11 01:08:05 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_builten(t_comd *msh)
{
	if (!msh->args || !msh->args[0])
		return (false);
	else if (!ft_strcmp(msh->args[0], "exit"))
		return (true);
	else if (!ft_strcmp(msh->args[0], "env"))
		return (true);
	else if (!ft_strcmp(msh->args[0], "cd"))
		return (true);
	else if (!ft_strcmp(msh->args[0], "echo"))
		return (true);
	else if (!ft_strcmp(msh->args[0], "pwd"))
		return (true);
	else if (!ft_strcmp(msh->args[0], "export"))
		return (true);
	else if (!ft_strcmp(msh->args[0], "unset"))
		return (true);
	return (false);
}
