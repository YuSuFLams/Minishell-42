/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export_utils_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:43:00 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/09/29 03:22:35 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*substring_before_equal(char *str)
{
	char	*equal_sign;
	size_t	length;
	char	*result;

	result = NULL;
	equal_sign = ft_strchr(str, '=');
	if (equal_sign != NULL)
	{
		if (equal_sign != str && *(equal_sign - 1) == '+')
			equal_sign--;
		length = equal_sign - str;
		result = (char *)malloc(length + 1);
		if (result != NULL)
		{
			ft_strncpy(result, str, length);
			result[length] = '\0';
		}
	}
	else
		result = ft_strdup(str);
	return (result);
}

char	*new_string(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*s_new;

	s_new = (char *)malloc((strlen(s) + 1) * sizeof(char));
	if (!s_new)
		return (NULL);
	i = 0;
	j = 0;
	len = findsubstring(s);
	while (*(s + i))
	{
		if (i == len)
		{
			i++;
			*(s_new + j) = *(s + i);
		}
		else
			*(s_new + j) = *(s + i);
		j++;
		i++;
	}
	*(s_new + j) = '\0';
	return (s_new);
}

char	**put_array(char **arr, char **new_arr, char *str)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i + 1] == NULL)
		{
			new_arr[i] = ft_strdup(str);
			new_arr[i + 1] = ft_strdup(arr[i]);
		}
		else
			new_arr[i] = ft_strdup(arr[i]);
		if (new_arr[i] == NULL)
		{
			freesplit(new_arr, 0);
			return (new_arr);
		}
		i++;
	}
	return (new_arr);
}

char	**loop_add_var(char **arr, char **new_arr, char *str)
{
	if (!arr[0])
	{
		new_arr[0] = ft_strdup(str);
		new_arr[1] = NULL;
	}
	else
		new_arr = put_array(arr, new_arr, str);
	return (new_arr);
}

char	**add_var_export(char **shell, char *str)
{
	char	**s;
	int		len;

	if (str[search_plus(str, '=')] == '\"')
		remove_quotes(str, '\"');
	if (str[search_plus(str, '=')] == '\'')
		remove_quotes(str, '\'');
	len = set_size_arg(shell);
	s = (char **)ft_calloc(sizeof(char *), (len + 2));
	if (!s)
		return (NULL);
	loop_add_var(shell, s, str);
	return (s);
}
