/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:54:01 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_way(char *cmd, t_shell *cm, t_comd *mini)
{
	char	*path_test;
	int		ret_path;
	int		len;

	path_test = find_path(cm, cmd);
	ret_path = chdir(path_test);
	len = ft_strlen(cmd) - 1;
	free(path_test);
	if (ret_path != 0)
	{
		cmd = ft_substr(cmd, 0, len);
		ft_putstr_fd("minishell : cd: ", mini->output_redirect);
		ft_putstr_fd(cmd, mini->output_redirect);
		free(cmd);
		ft_putstr_fd(" not set\n", mini->output_redirect);
		g_exit_cmd = 1;
	}
	return (ret_path);
}

void	add_up_to_env(t_shell *m_shell)
{
	int		i;
	char	*path;
	char	**s;

	s = m_shell->str;
	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(s[i], "PWD=", 4) && m_shell->_pwd)
		{
			path = ft_strjoin("PWD=", m_shell->_pwd);
			free(s[i]);
			s[i] = path;
		}
		else if (!ft_strncmp(s[i], "OLDPWD=", 7) && m_shell->_oldpwd)
		{
			path = ft_strjoin("OLDPWD=", m_shell->_oldpwd);
			free(s[i]);
			s[i] = path;
		}
		i++;
	}
}

void	change_path(t_shell *cmd, t_comd *mini)
{
	char	*new_pwd;
	char	*err;
	char	*s;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		err = ft_strjoin(ERR_GETCWD, strerror(errno));
		ft_putstr_fd(err, mini->output_redirect);
		ft_putchar_fd('\n', mini->output_redirect);
		free(err);
		s = cmd->_pwd;
		cmd->_pwd = ft_strjoin(s, "/..");
		free(s);
		return ;
	}
	free(cmd->_oldpwd);
	cmd->_oldpwd = cmd->_pwd;
	cmd->_pwd = new_pwd;
}

bool	check_cd_arg(t_shell *cmd, t_comd *mini)
{
	char	**s;

	s = cmd->cmnd;
	if (s && s[1] && s[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", \
		mini->output_redirect);
		g_exit_cmd = 1;
		return (false);
	}
	return (true);
}

void	shell_cd(t_shell *shell_m, t_comd *mini)
{
	int		ret;

	if (!check_cd_arg(shell_m, mini) || !test_home(shell_m))
		return ;
	if (!shell_m->cmnd[1] || !ft_strncmp(shell_m->cmnd[1], "~", 1) || \
	!ft_strncmp(shell_m->cmnd[1], "--", 2)) 
		ret = check_way("HOME=", shell_m, mini);
	else if (!ft_strncmp(shell_m->cmnd[1], "-", 1))
		ret = check_way("OLDPWD=", shell_m, mini);
	else
	{
		ret = chdir(shell_m->cmnd[1]);
		if (ret == -1)
		{
			print_errur_cd(shell_m->cmnd[1]);
			g_exit_cmd = 1;
		}
	}
	if (ret != 0)
		return ;
	change_path(shell_m, mini);
	add_up_to_env(shell_m);
	if (shell_m->cmnd[1] && !ft_strcmp(shell_m->cmnd[1], "-"))
		printf("%s\n", shell_m->_pwd);
	g_exit_cmd = 0;
}
