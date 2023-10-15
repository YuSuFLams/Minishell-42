/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:32:05 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_built(t_shell *m_sh, t_comd *mini)
{
	if (!ft_strcmp(m_sh->cmnd[0], "exit"))
		shell_exit(m_sh, mini);
	else if (!ft_strcmp(m_sh->cmnd[0], "env"))
		shell_env(m_sh, mini);
	else if (!ft_strcmp(m_sh->cmnd[0], "cd"))
		shell_cd(m_sh, mini);
	else if (!ft_strcmp(m_sh->cmnd[0], "echo"))
		shell_echo(m_sh, mini);
	else if (!ft_strcmp(m_sh->cmnd[0], "pwd"))
		shell_pwd(m_sh, mini);
	else if (!ft_strcmp(m_sh->cmnd[0], "export"))
		shell_export(m_sh, mini);
	else if (!ft_strcmp(m_sh->cmnd[0], "unset"))
		shell_unset(m_sh);
}

char	*get_path_acc(t_shell *mini, t_comd *cmd)
{
	char	*possible_path;
	char	*tmp;

	possible_path = NULL;
	if (!ft_strchr(cmd->args[0], '/'))
	{
		mini->cmnd = fill_input(cmd, mini);
		possible_path = get_access(mini);
	}
	else
		possible_path = ft_strdup(cmd->args[0]); 
	if (access(possible_path, F_OK | X_OK) == -1)
	{
		if (errno == 14)
			command_not_found(cmd->args[0]);
		else
		{
			tmp = ft_strjoin("minishell: ", cmd->args[0]);
			perror(tmp);
			free(tmp);
		}
		g_exit_cmd = 127;
		free(possible_path);
	}
	return (possible_path);
}
