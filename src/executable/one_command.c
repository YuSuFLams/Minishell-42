/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:35:07 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wit_exit(int pid)
{
	waitpid(pid, &g_exit_cmd, 0);
	if (WIFSIGNALED(g_exit_cmd))
		g_exit_cmd += 128;
	else
		g_exit_cmd %= 255;
}

void	one_command(t_shell *cmd, t_comd *mini, char *s)
{
	int	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, sig_child);
		signal(SIGQUIT, sig_child);
		if (mini->input_redirect > 1)
			dup2(mini->input_redirect, 0);
		if (mini->output_redirect >= 1)
			dup2(mini->output_redirect, 1);
		close_fd_open(mini);
		if (execve(s, cmd->cmnd, cmd->str) == -1)
			failed_execve(s, cmd);
		free(s);
	}
	else
	{
		wit_exit(pid);
		free(s);
		return ;
	}
}

void	set_command(t_shell *mini, t_comd *cmd, char *s)
{
	if (cmd->output_redirect != -1 && cmd->input_redirect != -1)
	{
		if (cmd->args[0][0] == '\0')
		{
			command_not_found(cmd->args[0]);
			g_exit_cmd = 127;
			return ;
		}
		mini->cmnd = fill_input(cmd, mini);
		if (is_builten(cmd))
			execute_built(mini, cmd);
		else
			if (execve(s, mini->cmnd, mini->str) == -1)
				failed_execve(s, mini);
		exit(g_exit_cmd);
		freesplit(mini->cmnd, 0);
	}
	else
		exit(g_exit_cmd);
}
