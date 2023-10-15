/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:55:47 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_single_hyphen_n(char *s)
{
	int	i;

	i = 0;
	if (s[0] != '-' || s[1] != 'n')
		return (false);
	i = 2;
	while (*(s + i))
	{
		if (*(s + i) != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	shell_echo(t_shell *cmd, t_comd *mini)
{
	int		i;
	bool	shell_test;
	int		pid;

	if (!mini->next)
		pid = mini->output_redirect;
	else
		pid = STDOUT_FILENO;
	i = 1;
	shell_test = true;
	while (cmd->cmnd[i] && is_single_hyphen_n(cmd->cmnd[i]))
	{
		shell_test = false;
		i++;
	}
	while (cmd->cmnd[i] != NULL)
	{
		ft_putstr_fd(cmd->cmnd[i], pid);
		if (cmd->cmnd[i++ + 1] != NULL)
			ft_putchar_fd(' ', pid);
	}
	if (shell_test)
		ft_putchar_fd('\n', pid);
	g_exit_cmd = 0;
}
