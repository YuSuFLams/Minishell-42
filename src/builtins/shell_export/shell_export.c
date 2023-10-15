/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:45:31 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	if_qoute_exit(t_shell *shell, char *s)
{
	char	**tmp;

	if (!find_command(shell, s))
	{
		if (s && !check_char(shell, s))
		{
			tmp = add_var_export(shell->str, s);
			freesplit(shell->str, 0);
			shell->str = tmp;
			g_exit_cmd = 0;
		}
	}
}

void	another_export(t_shell *shell_m, char *new_s, int i)
{
	char	*s;
	char	*str;
	char	**tmp;
	char	*tmp1;
	int		len;

	tmp = NULL;
	len = set_size_arg(shell_m->str);
	tmp1 = extract_before_plus(new_s);
	if (search_p_q(new_s, '+') && !check_input(tmp1) \
	&& find_cmd_exist_plus(shell_m->str, new_s))
	{
		if (new_s && check_plus_equal(shell_m, new_s))
			add_cmnd(shell_m, len, i, tmp);
	}
	else
	{
		s = remove_first_plus(shell_m->cmnd[i]);
		str = new_string(s);
		if_qoute_exit(shell_m, str);
		free(str);
		free(s);
	}
	free(tmp1);
}

void	test_export(t_shell *shell_m, int i)
{
	char	**tmp;
	char	*new_s;

	tmp = NULL;
	new_s = shell_m->cmnd[i];
	if (empty_line(new_s))
		test_err_ex(shell_m, new_s);
	else if (!search_plus(new_s, '='))
	{
		if (check_cmd_exp(shell_m, new_s))
			return ;
		if (check_input(new_s))
			export_unset_err(shell_m->cmnd[0], new_s);
		else
		{
			tmp = add_var_export(shell_m->str, new_s);
			freesplit(shell_m->str, 0);
			shell_m->str = tmp;
			g_exit_cmd = 0;
		}
	}
	else
		another_export(shell_m, new_s, i);
}

void	shell_export(t_shell *sh, t_comd *mini)
{
	int		i;
	char	**s;

	i = 1;
	s = sh->cmnd;
	if (!s[1])
		shell_env(sh, mini);
	else
	{
		while (s[i])
		{
			test_export(sh, i);
			i++;
		}
	}
}
