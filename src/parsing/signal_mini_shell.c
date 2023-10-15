/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_mini_shell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:21:45 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sig_ctlc(int input_sig)
{
	if (input_sig == SIGINT)
	{
		g_exit_cmd = 1;
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_replace_line("", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_quit(int input_sig)
{
	write(STDERR_FILENO, "Quit: ", 6);
	ft_putnbr_fd(input_sig, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}

void	signal_def(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	all_signals(void)
{
	signal(SIGINT, sig_ctlc);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_child(int input_sig)
{
	if (input_sig == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
		exit(131);
	}
	else if (input_sig == SIGINT)
		exit(130);
}
