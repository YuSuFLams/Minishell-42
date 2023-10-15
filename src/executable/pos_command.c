/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:19:34 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	first_cmd(t_shell *mini, t_comd *cmd, int **fd, int *i)
{
	char	*s;
	int		pid;

	s = NULL;
	if (!(*i))
	{
		pipe(fd[*i]);
		pid = fork();
		if (pid == -1)
			g_exit_cmd = 1;
		else if (!pid)
		{
			signal(SIGINT, sig_child);
			signal(SIGQUIT, sig_child);
			if (g_exit_cmd == 1)
				exit(g_exit_cmd);
			if (!is_builten(cmd))
				s = get_path_acc(mini, cmd);
			dup_com_pos(cmd, fd, *i, 1);
			set_command(mini, cmd, s);
			exit(g_exit_cmd);
		}
	}
}

void	wait_pid_last(int pid, int **fd, int *i)
{
	close(fd[*i][0]);
	close(fd[*i][1]);
	if (waitpid(pid, &g_exit_cmd, 0) != -1)
	{
		if (WIFSIGNALED(g_exit_cmd))
			g_exit_cmd += 128;
		else
			g_exit_cmd %= 255;
	}
}

void	last_command(t_shell *mini, t_comd *cmd, int **fd, int *i)
{
	char	*s;
	int		pid;

	s = NULL;
	if (!cmd->next)
	{
		g_exit_cmd = 0;
		pid = fork();
		if (pid == -1)
			g_exit_cmd = 1;
		else if (!pid)
		{
			signal(SIGINT, sig_child);
			signal(SIGQUIT, sig_child);
			if (g_exit_cmd == 1)
				exit(g_exit_cmd);
			if (!is_builten(cmd))
				s = get_path_acc(mini, cmd);
			dup_com_pos(cmd, fd, *i, 3);
			set_command(mini, cmd, s);
			exit(g_exit_cmd);
		}
		wait_pid_last(pid, fd, i);
	}
}

void	comand_between(t_shell *mini, t_comd *cmd, int **fd, int *i)
{
	char	*s;
	int		pid;

	s = NULL;
	if (cmd->next)
	{
		pipe(fd[++(*i)]);
		close(fd[(*i) - 1][1]);
		pid = fork();
		if (pid == -1)
			check_that();
		else if (!pid)
		{
			signal(SIGINT, sig_child);
			signal(SIGQUIT, sig_child);
			if (g_exit_cmd == 1)
				exit(g_exit_cmd);
			if (!is_builten(cmd))
				s = get_path_acc(mini, cmd);
			dup_com_pos(cmd, fd, *i, 2);
			set_command(mini, cmd, s);
			exit(g_exit_cmd);
		}
	}
}

void	execute_another_command(t_shell *shell, t_comd *cmd)
{
	t_comd	*tmp;
	int		**fd;
	int		len;
	int		i;

	tmp = cmd;
	len = size_cmd(cmd);
	fd = (int **)ft_calloc(sizeof(int *), (len - 1));
	i = len - 2;
	while (i >= 0)
		fd[i--] = (int *)ft_calloc(sizeof(int), 2);
	i = 0;
	while (cmd->next)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		first_cmd(shell, cmd, fd, &i);
		close_fd_open(cmd);
		cmd = cmd->next;
		last_command(shell, cmd, fd, &i);
		comand_between(shell, cmd, fd, &i);
		close_fd_open(cmd);
	}
	close_all_fd(tmp, fd);
}
