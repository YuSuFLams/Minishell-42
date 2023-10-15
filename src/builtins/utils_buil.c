/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_buil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 05:12:37 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	search_p_q(char *s, char d_quot)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == d_quot && s[i + 1] == '=')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (0);
}

void	add_cmnd(t_shell *shell_m, int len, int i, char **tmp)
{
	tmp = add_if_plus_exit(shell_m->str, shell_m->cmnd[i], len);
	freesplit(shell_m->str, 0);
	shell_m->str = tmp;
	g_exit_cmd = 0;
}

char	**bubble_sort(char **str)
{
	int	num_s;
	int	i;
	int	j;

	num_s = set_size_arg(str);
	i = 0;
	while (i < num_s - 1)
	{
		j = 0;
		while (j < num_s - i - 1)
		{
			if (ft_strcmp(str[j], str[j + 1]) > 0)
				ft_swap(&str[j], &str[j + 1]);
			j++;
		}
		i++;
	}
	return (str);
}

bool	test_home(t_shell *cmd)
{
	int		i;
	char	**s;
	char	*key;
	char	*value;

	i = 0;
	s = cmd->str;
	while (s[i])
	{
		key = extract_before_equal(s[i]);
		value = extract_after_equal(s[i]);
		if (!ft_strcmp(key, "HOME"))
		{
			if (value && !ft_strlen(value) && search_plus(s[i], '='))
				return (free(key), free(value), false);
			else
				return (free(key), free(value), true);
		}
		free(key);
		free(value);
		i++;
	}
	return (true);
}
