/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:50:15 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	another_exit(char *s, t_comd *mini)
{
	long long int	exit_stat;

	exit_stat = atoi_exit(s);
	if (errno == ERANGE)
	{
		print_errur_exit(s);
		g_exit_cmd = 255;
	}
	else
	{
		ft_putstr_fd("\033[1;34mexit\n\033[0m", mini->output_redirect);
		g_exit_cmd = exit_stat;
	}
}

void	shell_exit(t_shell *cmd, t_comd *mini)
{
	if (!cmd->cmnd[1])
	{
		ft_putstr_fd("\033[1;32mexit\n\033[0m", mini->output_redirect);
		exit(g_exit_cmd);
	}
	else if (is_all_digit(cmd->cmnd[1]) && cmd->cmnd[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		g_exit_cmd = 1;
		return ;
	}
	else if (is_all_digit(mini->args[1]))
		another_exit(mini->args[1], mini);
	else
	{
		print_errur_exit(cmd->cmnd[1]);
		g_exit_cmd = 255;
	}
	exit(g_exit_cmd);
}
