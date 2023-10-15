/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:27:25 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	single_command(t_shell *m_sh, t_comd *mini)
{
	char	*possible_path;
	char	*tmp;

	if (!ft_strchr(m_sh->cmnd[0], '/'))
		possible_path = get_access(m_sh);
	else
		possible_path = ft_strdup(m_sh->cmnd[0]);
	if (access(possible_path, X_OK) == -1)
	{
		if (errno == 14)
			command_not_found(m_sh->cmnd[0]);
		else
		{
			tmp = ft_strjoin("minishell: ", m_sh->cmnd[0]);
			perror(tmp);
			free(tmp);
		}
		g_exit_cmd = 127;
		free(possible_path);
		return ;
	}
	one_command(m_sh, mini, possible_path);
	all_signals();
}

void	close_fd_open(t_comd *cmd)
{
	if (cmd->input_redirect > 1)
		close(cmd->input_redirect);
	if (cmd->output_redirect > 1)
		close(cmd->output_redirect);
}

void	check_empty(t_comd *cmd)
{
	if (cmd->args[0][0] == '\0')
	{
		command_not_found(cmd->args[0]);
		g_exit_cmd = 127;
	}
}

void	execute_it(t_comd *cmd, t_shell *m_sh)
{
	if (!cmd->next)
	{
		if (cmd->input_redirect == -1 || cmd->output_redirect == -1)
			return ;
		if (cmd && cmd->args[0][0] == '\0')
			check_empty(cmd);
		m_sh->cmnd = fill_input(cmd, m_sh);
		if (m_sh->cmnd[0] && m_sh->cmnd[0][0])
		{
			single_command(m_sh, cmd);
			close_fd_open(cmd);
		}
		else
		{
			freesplit(m_sh->cmnd, 0);
			return ;
		}
		freesplit(m_sh->cmnd, 0);
		all_signals();
		return ;
	}
	else
		execute_another_command(m_sh, cmd);
}

void	mini_exec(t_shell *m_sh, t_comd *parsed_cmd)
{
	if (!parsed_cmd || (!parsed_cmd->args && !parsed_cmd->next))
		return ;
	if (size_cmd(parsed_cmd) == 1 && is_builten(parsed_cmd))
	{
		m_sh->cmnd = fill_input(parsed_cmd, m_sh);
		execute_built(m_sh, parsed_cmd);
		freesplit(m_sh->cmnd, 0);
		return ;
	}
	else
		execute_it(parsed_cmd, m_sh);
}
