/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 04:35:51 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	err_in_dir(DIR *dir, char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": is a directory\n", STDERR_FILENO);
	closedir(dir);
}

void	print_errur_cd(char *s)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	perror(s);
}

void	print_errur_exit(char *s)
{
	ft_putstr_fd("\033[1;31mexit\n\033[0mminishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

void	command_not_found(char *s)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

int	export_unset_err(char *cmd, char *s)
{
	g_exit_cmd = 1;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (s != NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": `", STDERR_FILENO);
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putstr_fd("': is ", STDERR_FILENO);
	}
	ft_putstr_fd("not a valid identifier", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (EXIT_FAILURE);
}
