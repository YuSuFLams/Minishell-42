/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 22:43:12 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	failed_execve(char *path, t_shell *lines)
{
	DIR	*dir;

	if (!path)
		exit(g_exit_cmd = 127);
	dir = opendir(path);
	if (dir)
	{
		err_in_dir(dir, lines->cmnd[0]);
		g_exit_cmd = 126;
		free(path);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(lines->cmnd[0]);
		free(path);
		g_exit_cmd = 126;
	}
	exit(g_exit_cmd);
}

static void	close_all(t_comd *cmd, int **fd)
{
	int		i;

	i = size_cmd(cmd) - 2;
	while (i >= 0)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		free(fd[i]);
		i--;
	}
}

void	close_all_fd(t_comd *cmd, int **fd)
{
	close_all(cmd, fd);
	free(fd);
	while (wait(NULL) != -1)
		;
	all_signals();
}

void	dup_pipe_extra(t_comd *cmd, int **fd, int i, int flag)
{
	if (flag == 1)
	{
		if (cmd->output_redirect != -1)
			dup2(cmd->output_redirect, 1);
		close(fd[i][0]);
		if (cmd->output_redirect != -1)
			dup2(fd[i][1], cmd->output_redirect);
	}
	else if (flag == 2)
	{
		if (cmd->input_redirect != -1)
			dup2(fd[i - 1][0], cmd->input_redirect);
		if (cmd->output_redirect != -1)
			dup2(fd[i][1], cmd->output_redirect);
	}
	else if (flag == 3)
	{
		if (cmd->input_redirect != -1)
			dup2(fd[i][0], cmd->input_redirect);
		if (cmd->output_redirect != -1)
			dup2(cmd->output_redirect, 1);
	}
}

void	dup_com_pos(t_comd *cmd, int **fd, int i, int flag)
{
	if (cmd->input_redirect != -1)
		dup2(cmd->input_redirect, 0);
	if (flag == 1)
	{
		dup_pipe_extra(cmd, fd, i, 1);
		close(fd[i][1]);
	}
	else if (flag == 2)
	{
		dup2(cmd->output_redirect, 1);
		close(fd[i][0]);
		dup_pipe_extra(cmd, fd, i, 2);
		close(fd[i][1]);
		close(fd[i - 1][0]);
	}
	else if (flag == 3)
	{
		close(fd[i][1]);
		dup_pipe_extra(cmd, fd, i, 3);
		close(fd[i][0]);
	}
}
