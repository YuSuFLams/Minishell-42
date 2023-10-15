/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar_utils_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 00:55:00 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/14 21:45:46 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*do_qeus(char *tmp, int len, char *tmp_str)
{
	char	*tmp2;

	tmp2 = (char *)malloc(ft_strlen(tmp) + len + 1);
	if (!tmp2)
		return (NULL);
	ft_strcpy(tmp2, tmp);
	ft_strcat(tmp2, tmp_str);
	free(tmp);
	tmp = tmp2;
	return (tmp);
}

int	length_after_do(int pos_dol, char *s)
{
	int	i;

	i = pos_dol + 1;
	while (*(s + i) != '\0' && *(s + i) != '$' && *(s + i) != ' ' 
		&& *(s + i) != '+' && *(s + i) != '\"' && *(s + i) != '\'' 
		&& *(s + i) != '=' && *(s + i) != '-' && *(s + i) != ':' 
		&& *(s + i) != '/' && *(s + i) && *(s + i) != '~')
		i++;
	return (i);
}

char	*another_after(char *tmp, char *s, int i)
{
	char	*tmp2;
	char	*tmp3;

	tmp2 = join_char(s[i]);
	tmp3 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	tmp = tmp3;
	return (tmp);
}

char	*expander_cmd(char *str, t_shell *cmd)
{
	char	*tmp;
	int		pos_d;

	tmp = NULL;
	pos_d = search_plus(str, '$');
	if (pos_d != 0 && str[pos_d] != '\0')
	{
		tmp = set_if_do(cmd, str, 0);
		free(str);
		str = tmp;
	}
	return (str);
}
