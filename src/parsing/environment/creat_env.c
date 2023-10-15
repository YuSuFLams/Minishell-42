/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:00:01 by ssaadaou          #+#    #+#             */
/*   Updated: 2023/10/02 01:07:15 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_env_list(t_env *head)
{
	t_env	*current;
	t_env	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

t_env	*create_env_node(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	append_env_node(t_env **head, char *key, char *value)
{
	t_env	*tmp;

	if (!*head)
	{
		*head = create_env_node(key, value);
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = create_env_node(key, value);
}

t_env	*fill_env_list(char **env)
{
	t_env	*head;
	int		i;
	char	*value;
	char	*key;

	i = 0;
	head = NULL;
	while (env[i])
	{
		split_env_line(env[i], &key, &value);
		append_env_node(&head, key, value);
		free(key);
		free(value);
		i++;
	}
	return (head);
}

char	**put_list_in_array(t_env *lst_env)
{
	int		size_env;
	int		i;
	char	**s;
	char	*tmp; 

	size_env = lst_size_cmd(lst_env);
	s = (char **)malloc((size_env + 1) * sizeof(char *));
	if (!s)
		return (perror("Memory allocation error"), NULL);
	i = 0;
	while (lst_env)
	{
		tmp = ft_strjoin(lst_env->key, "=");
		s[i] = ft_strjoin(tmp, lst_env->value);
		free(tmp);
		i++;
		lst_env = lst_env->next;
	}
	s[i] = NULL;
	return (s);
}
