/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 01:17:58 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	check_qoutes(char *input, t_shell *cmnd)
{
	int		i;
	int		j;
	char	quote;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			j = i;
			while (input[++j])
			{
				if (input[j] == quote)
				{
					cmnd->input_err = quote;
					break ;
				}
			}
			if (!input[j])
				return (false);
			i = j;
		}
	}
	return (true);
}

bool	check_syntex_input(char *input, t_shell *cmd)
{
	if (!check_qoutes(input, cmd))
	{
		ft_putstr_fd(ERRSYN, STDERR_FILENO);
		ft_putchar_fd(cmd->input_err, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		free(input);
		return (false);
	}
	return (true);
}

void	check_that(void)
{
	if (g_exit_cmd != 1)
		perror("Minishell: ");
	g_exit_cmd = 1;
}
