/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 19:10:20 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	shell_pwd(t_shell *cmd, t_comd *mini)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putstr_fd(cwd, mini->output_redirect);
		ft_putchar_fd('\n', mini->output_redirect);
		return ;
	}
	else
	{
		ft_putstr_fd(cmd->_pwd, mini->output_redirect);
		ft_putchar_fd('\n', mini->output_redirect);
	}
	g_exit_cmd = 0;
}
