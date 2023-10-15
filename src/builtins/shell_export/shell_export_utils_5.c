/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export_utils_5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 01:23:38 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*extract_before_equal(char *s)
{
	char	*pos;
	size_t	len;
	char	*new_s;

	pos = ft_strchr(s, '=');
	if (!pos)
		return (ft_strdup(s));
	len = pos - s;
	new_s = (char *)malloc((len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	ft_strncpy(new_s, s, len);
	new_s[len] = '\0';
	return (new_s);
}

char	*remove_first_plus(char *str)
{
	char	*pos;
	size_t	len;
	char	*s;
	char	*tmp;

	pos = ft_strstr(str, "+=");
	if (pos)
	{
		tmp = ft_substr(str, 0, pos - str);
		if (check_input(tmp))
			return (free(tmp), ft_strdup(str));
		free(tmp);
	}
	if (!pos)
		return (ft_strdup(str));
	len = ft_strlen(str) - 1;
	s = (char *)malloc(len + 1);
	if (!s)
		return (NULL);
	ft_strncpy(s, str, pos - str);
	ft_strcpy(s + (pos - str), pos + 1);
	return (s);
}

void	test_err_ex(t_shell *shell_m, char *new_s)
{
	export_unset_err(shell_m->cmnd[0], new_s);
	g_exit_cmd = 1;
	return ;
}
