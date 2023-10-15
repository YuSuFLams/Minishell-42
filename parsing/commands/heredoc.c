/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaadaou <ssaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 02:02:55 by ssaadaou          #+#    #+#             */
/*   Updated: 2023/10/10 22:48:35 by ssaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/ioctl.h>

void	handler_c(int sig)
{
	(void)sig;
	g_exit_cmd = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	ioctl(0, TIOCSTI, "\4");
}

void	sig_heredoc(void)
{
	signal(SIGINT, handler_c);
	signal(SIGQUIT, SIG_IGN);
}

int	handle_heredoc(char *del, t_shell *mini)
{
	int		fd[2];
	char	*str;

	str = NULL;
	g_exit_cmd = 0;
	if (pipe(fd) == -1) 
		return (-1);
	while (1) 
	{
		sig_heredoc();
		str = readline("heredoc> ");
		if (str == NULL ) 
		{
			close(fd[1]);
			free(str);
			break ;
		}
		if (!search_plus(del, '$'))
			str = expander_cmd(str, mini);
		if (ft_strcmp(str, del) == 0) 
			return (free(str), close(fd[1]), fd[0]);
		ft_putendl_fd(str, fd[1]);
		free(str);
	}
	return (fd[0]);
}

int	heredoc_case(t_list *tokens, t_shell *mini)
{
	t_list	*curr;
	int		fd;

	fd = 0;
	curr = tokens;
	if (curr && curr->type == word)
	{
		fd = handle_heredoc(curr->cmd, mini);
		free(curr->cmd);
	}
	else if (curr->next && curr->next->type == word)
	{
		fd = handle_heredoc(curr->next->cmd, mini);
		free(curr->next->cmd);
	}
	return (fd);
}

void	init_new_cmd(t_comd **curr)
{
	t_comd	*new_cmd;

	new_cmd = init_cmds();
	if (*curr)
	{
		(*curr)->next = new_cmd;
		(*curr) = (*curr)->next;
	}
	else
		(*curr) = new_cmd; 
}
