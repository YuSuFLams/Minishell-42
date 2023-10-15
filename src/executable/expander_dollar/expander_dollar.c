/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 22:08:49 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	if_dollar_exist(t_shell *cmd, char *str, char **tmp, int j)
{
	int		i;
	int		ret;
	char	*s1;
	char	*s2;
	int		p_equal;

	i = -1;
	ret = 0;
	while (cmd->str[++i])
	{
		p_equal = search_plus(cmd->str[i], '=');
		if (!ft_strncmp(str + j + 1, cmd->str[i], p_equal - 1)
			&& length_after_do(j, str) - j == p_equal)
		{
			s1 = ft_strdup(cmd->str[i] + p_equal);
			s2 = ft_strjoin(*tmp, s1);
			free(*tmp);
			*tmp = s2;
			free(s1);
			ret = p_equal;
		}
	}
	if (!ret)
		ret = length_after_do(j, str) - j;
	return (ret);
}

char	*set_if_do(t_shell *cmd, char *s, int i)
{
	char	*tmp;
	char	*str;

	tmp = ft_strdup("");
	while (s[i])
	{
		i += check_int_after_dol(s, i);
		if (s[i] == '$' && aftre_do(*(s + i + 1)))
		{
			str = ft_itoa(g_exit_cmd);
			tmp = strjoin_another(tmp, str);
			i += 2;
		}
		else if (aftre_do_1(s, i))
			i += if_dollar_exist(cmd, s, &tmp, i);
		else
		{
			tmp = another_after(tmp, s, i);
			i++;
		}
	}
	return (tmp);
}

char	**cpy_command_echo(t_shell *cmd, char **s)
{
	char	**new_s;
	int		i;
	int		j;
	int		len;

	len = set_size_arg(s);
	new_s = (char **)ft_calloc(sizeof(char *), len + 1);
	if (!new_s)
		return (NULL);
	j = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], "~"))
			new_s[j++] = ft_strdup(cmd->home);
		else
			new_s[j++] = ft_strdup(s[i]);
		i++;
	}
	new_s[j] = NULL;
	return (new_s);
}

char	**expand_name(char **s, t_shell *cmd)
{
	int		p_do;
	char	**new_s;
	char	*tmp;
	int		i;

	new_s = NULL;
	new_s = cpy_command_echo(cmd, s);
	if (new_s[0][0] == '\"')
		new_s[0] = remove_quotes(new_s[0], '\"');
	else if (new_s[0][0] == '\'')
		new_s[0] = remove_quotes(new_s[0], '\'');
	i = 0;
	while (new_s[i])
	{
		p_do = search_plus(new_s[i], '$');
		if (new_s[i][p_do - 2] != '\'' && p_do && new_s[i][p_do] != '\0')
		{
			tmp = set_if_do(cmd, new_s[i], 0);
			free(new_s[i]);
			new_s[i] = tmp;
		}
		i++;
	}
	return (new_s);
}
