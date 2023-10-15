/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:56:46 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:17 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*print_minishell(char *input)
{
	if (!g_exit_cmd)
		input = readline(MESSAGE_COR);
	else
		input = readline(MESSAGE_FAL);
	return (input);
}

void	free_all_minishell(t_shell *cmd, t_env *head)
{
	free_env_list(head);
	freesplit(cmd->str, 0);
	free(cmd->_oldpwd);
	free(cmd->path_all);
	free(cmd->home);
	free(cmd->_pwd);
	free(cmd);
}

int	main(int ac, char **str, char **envv)
{
	t_shell	*cmd;
	t_env	*head;

	(void)str;
	if (!isatty(0))
		return (0);
	if (ac == 1)
	{
		printf("%s\n", WELCOME);
		cmd = malloc(sizeof(t_shell));
		if (!cmd)
			return (0);
		head = fill_env_list(envv);
		cmd->str = put_list_in_array(head);
		search_p_o_p(cmd);
		mini_shell_w(cmd);
		free_all_minishell(cmd, head);
	}
	else
	{
		printf("\033[0;31mMinishell: Does Not Accept Arguments 😠💢!!\n\033[0m");
		exit(EXIT_FAILURE);
	}
	return (0);
}
