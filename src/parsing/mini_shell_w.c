/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_w.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:34:38 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**fill_input(t_comd *source, t_shell *cmd)
{
	t_comd	*a;
	int		len;
	int		i;
	char	**s;
	char	**new_s;

	a = source;
	len = set_size_arg(a->args);
	if (!a->args)
		return (NULL);
	new_s = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (a->args[i])
	{
		new_s[i] = ft_strdup(a->args[i]);
		i++;
	}
	new_s[i] = NULL;
	s = cpy_command_echo(cmd, new_s);
	freesplit(new_s, 0);
	return (s);
}

void	clear_list_all(t_comd *parsed_cmd)
{
	t_comd	*tmp;

	tmp = NULL;
	if (parsed_cmd && parsed_cmd->args)
	{
		while (parsed_cmd)
		{
			if (parsed_cmd->input_redirect > 0)
				close(parsed_cmd->input_redirect);
			if (parsed_cmd->output_redirect > 1)
				close(parsed_cmd->output_redirect);
			freesplit(parsed_cmd->args, 0);
			tmp = parsed_cmd;
			parsed_cmd = parsed_cmd->next;
			free(tmp);
		}
	}
	free(parsed_cmd);
}

void	execu_pars(char *input, t_shell *cmd, t_comd *par_cmd, t_list *mini)
{
	if (!check_syntex_input(input, cmd))
		g_exit_cmd = 258;
	else
	{
		if (parse_command(cmd, input, &mini, &par_cmd))
		{
			mini_exec(cmd, par_cmd);
			clear_list_all(par_cmd);
		}
	}
}

void	exit_mini_shell(void)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit (g_exit_cmd);
	rl_clear_history();
}

void	mini_shell_w(t_shell *cmd)
{
	char	*input;
	t_comd	*parsed_cmd;
	t_list	*command;

	input = NULL;
	all_signals();
	command = NULL;
	parsed_cmd = NULL;
	while (1) 
	{
		command = NULL;
		parsed_cmd = NULL;
		input = print_minishell(input);
		add_history(input);
		if (!input)
		{
			exit_mini_shell();
			break ;
		}
		if (input[0] == '\0')
			free(input);
		else
			execu_pars(input, cmd, parsed_cmd, command);
	}
}
