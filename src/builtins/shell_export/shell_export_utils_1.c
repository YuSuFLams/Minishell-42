/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 23:17:41 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/12 05:55:07 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*remove_quotes(char *s, char c)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(s);
	i = 0;
	j = 0;
	while (*(s + i))
	{
		if (*(s + i) == c)
		{
			j = i;
			while (s[j] == c)
				j++;
			ft_memmove(&*(s + i), &s[j], len - j + 1);
		}
		else
			i++;
	}
	return (s);
}

int	check_valid_id(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || \
	c == ']' || c == '\'' || c == '\"' || c == ' ' || \
	c == ',' || c == '.' || c == ':' || c == '/' || \
	c == '{' || c == '}' || c == '+' || c == '^' || \
	c == '%' || c == '#' || c == '@' || c == '!' || \
	c == '~' || c == '=' || c == '-' || c == '?' || \
	c == '&' || c == '*' || c == ')' || c == '(' || \
	c == '\\' || c == ';');
}

int	check_input(char *s)
{
	int	i;

	i = 0;
	if (ft_isdigit(s[0]))
		return (EXIT_FAILURE);
	while (*(s + i))
	{
		if (check_valid_id(*(s + i)))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_char(t_shell *cmd, char *s)
{
	int	i;
	int	len;

	if (ft_isdigit(s[0]))
		return (export_unset_err(cmd->cmnd[0], s));
	if (search_plus(s, '=') == 0)
		return (EXIT_FAILURE);
	if (s[0] == '=')
		return (export_unset_err(cmd->cmnd[0], s));
	i = 0;
	len = find_first_equal_or_length(s);
	while (i < len)
	{
		if (check_valid_id(*(s + i)))
			return (export_unset_err(cmd->cmnd[0], s));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	find_cmd_exist_plus(char **s, char *sh_cmnd)
{
	int		i;
	char	*new_add;
	char	*new_str;

	i = 0;
	if (sh_cmnd[search_plus(sh_cmnd, '=')] == '\"')
		remove_quotes(sh_cmnd, '\"');
	if (sh_cmnd[search_plus(sh_cmnd, '=')] == '\'')
		remove_quotes(sh_cmnd, '\'');
	new_add = extract_before_plus(sh_cmnd);
	while (s[i] != NULL)
	{
		new_str = substring_before_equal(s[i]);
		if (!ft_strcmp(new_str, new_add))
			return (free(new_str), free(new_add), 1);
		else
			i++;
		free(new_str);
	}
	free(new_add);
	return (0);
}
