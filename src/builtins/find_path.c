/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:04:17 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/13 21:18:41 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	findsubstring(char *str)
{
	int	length;
	int	i;

	i = 0;
	length = ft_strlen(str);
	while (i < length)
	{
		if ((str[i] == '\"' && str[i + 1] == '=') \
		|| (str[i] == '\'' && str[i + 1] == '='))
			return (i);
		else
			i++;
	}
	return (-1);
}

char	*get_path(char **split, char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (split[i])
	{
		res = ft_strjoin(split[i], str);
		if (access(res, F_OK) == 0)
			break ;
		free(res);
		i++;
	}
	return (res);
}

char	*get_access(t_shell *cmd)
{
	char	*command;
	char	*path;
	char	**nwe_s;
	char	**split_path;
	char	*possible_path;

	if (ft_strchr(cmd->cmnd[0], ' '))
	{
		nwe_s = ft_split(cmd->cmnd[0], ' ');
		freesplit(cmd->cmnd, 0);
		cmd->cmnd = nwe_s;
	}
	command = ft_strjoin("/", cmd->cmnd[0]);
	path = find_path(cmd, "PATH");
	if (!cmd->path_all && !cmd->flag)
		path = ft_strdup(SPATH);
	split_path = ft_split(path, ':');
	free(path);
	if (!split_path || !split_path[0])
		return (free(split_path), free(command), NULL);
	possible_path = get_path(split_path, command);
	if (access(possible_path, F_OK))
		possible_path = NULL;
	return (free(command), freesplit(split_path, 0), possible_path);
}

void	search_p_o_p(t_shell *cmd)
{
	char	**s;
	int		i;

	s = cmd->str;
	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(s[i], "PWD=", 4))
			cmd->_pwd = ft_substr(s[i], 4, ft_strlen(s[i]) - 4);
		if (!ft_strncmp(s[i], "HOME=", 5))
			cmd->home = ft_substr(s[i], 5, ft_strlen(s[i]) - 5);
		if (!ft_strncmp(s[i], "PATH=", 5))
		{
			cmd->path_all = ft_substr(s[i], 5, ft_strlen(s[i]) - 5);
			cmd->flag = 1;
		}
		if (!ft_strncmp(s[i], "OLDPWD=", 7))
			cmd->_oldpwd = ft_substr(s[i], 7, ft_strlen(s[i]) - 7);
		i++;
	}
}

char	*find_path(t_shell *mini_s, char *find)
{
	int		i;
	int		len;
	char	**s;
	char	*path;

	s = mini_s->str;
	len = ft_strlen(find);
	path = NULL;
	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(s[i], find, len))
			path = ft_substr(s[i], len, ft_strlen(s[i]) - len);
		i++;
	}
	return (path);
}
