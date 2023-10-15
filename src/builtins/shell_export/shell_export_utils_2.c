/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:36:06 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/12 05:54:54 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	find_first_equal_or_length(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (len);
}

int	search_plus(char *s, char d_quot)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == d_quot)
		{
			i++;
			return (i);
		}
		i++;
	}
	return (0);
}

bool	check_cmd_exp(t_shell *sh_m, char *cmd)
{
	int		i;
	char	*first;
	char	*new_cmd;

	i = 0;
	new_cmd = extract_before_equal(cmd);
	while (sh_m->str[i])
	{
		first = extract_before_equal(sh_m->str[i]);
		if (!ft_strcmp(first, new_cmd))
			return (free(new_cmd), free(first), true);
		free(first);
		i++;
	}
	free(new_cmd);
	return (false);
}

char	*remove_double_quotes(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0 && (str[0] == '"' || str[0] == '\''))
	{
		ft_memmove(str, str + 1, len);
		len--;
	}
	if (len > 0 && (str[len - 1] == '"' || str[len - 1] == '\'')) 
		str[len - 1] = '\0';
	return (str);
}

int	find_command(t_shell *shell_m, char *sh_cmnd)
{
	char	*new_add;
	char	*new_str;
	int		i;

	i = 0;
	if (sh_cmnd[search_plus(sh_cmnd, '=')] == '\"')
		remove_quotes(sh_cmnd, '\"');
	if (sh_cmnd[search_plus(sh_cmnd, '=')] == '\'')
		remove_quotes(sh_cmnd, '\'');
	new_add = substring_before_equal(sh_cmnd);
	while (shell_m->str[i])
	{
		new_str = substring_before_equal(shell_m->str[i]);
		if (!ft_strcmp(new_str, new_add))
		{
			free(shell_m->str[i]);
			shell_m->str[i] = ft_strdup(sh_cmnd);
			return (free(new_str), free(new_add), 1);
		}
		free(new_str);
		i++;
	}
	free(new_add);
	return (0);
}
