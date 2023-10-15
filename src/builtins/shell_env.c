/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:58:12 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strd(char *s, t_shell *sh_m)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)ft_calloc(sizeof(char ), (ft_strlen(s) + 3));
	if (!str)
		return (str);
	i = -1;
	j = 0;
	sh_m->test = true;
	while (*(s + ++i))
	{
		if (*(s + i) == '=' && sh_m->test == true)
		{
			*(str + j++) = *(s + i);
			*(str + j++) = '"';
			sh_m->test = false;
		}
		else
			*(str + j++) = *(s + i);
	}
	if (!sh_m->test)
		*(str + j++) = '"';
	*(str + j) = '\0';
	return (str);
}

void	check_env_export(t_shell *cmd, char **s, t_comd *mini)
{
	int	j;

	if (!ft_strcmp(cmd->cmnd[0], "export"))
		s = bubble_sort(s);
	j = 0;
	while (s[j])
	{
		if (search_plus(s[j], '=') && !ft_strcmp(cmd->cmnd[0], "env"))
		{
			ft_putstr_fd(s[j], mini->output_redirect);
			ft_putchar_fd('\n', mini->output_redirect);
		}
		else if (!ft_strcmp(cmd->cmnd[0], "export"))
		{
			ft_putstr_fd(s[j], mini->output_redirect);
			ft_putchar_fd('\n', mini->output_redirect);
		}
		j++;
	}
}

char	*put_declare(t_shell *cmd, char *tmp)
{
	if (!ft_strcmp(cmd->cmnd[0], "export") && cmd->cp)
	{
		tmp = "declare -x ";
		cmd->cp = ft_strd(cmd->cp, cmd);
	}
	else
		tmp = "";
	return (tmp);
}

void	shell_env(t_shell *cmd, t_comd *mini)
{
	int		i;
	int		j;
	char	**s;
	char	*tmp;

	s = malloc(sizeof(char *) * (set_size_arg(cmd->str) + 1));
	if (!s)
		return ;
	i = 0;
	j = 0;
	while (cmd->str[i])
	{
		cmd->cp = cmd->str[i];
		tmp = put_declare(cmd, tmp);
		s[j++] = ft_strjoin(tmp, cmd->cp);
		if (!ft_strcmp(cmd->cmnd[0], "export"))
			free(cmd->cp);
		i++;
	}
	s[j] = NULL;
	check_env_export(cmd, s, mini);
	freesplit(s, 0);
	g_exit_cmd = 0;
}
