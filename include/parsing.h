/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:24:03 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:19:58 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum s_type
{
	space,
	word,
	p_pipe,
	input,
	output,
	output_append,
	heredoc,
	s_quote,
	d_quote,
	VAR,
}	t_type;

typedef struct s_list
{
	char			*cmd;
	int				type;
	t_type			token;
	int				content;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_comd 
{
	int				append;
	char			**args;
	int				input_redirect;
	int				output_redirect;
	struct s_comd	*next;
	struct s_comd	*prev;
	int				heredoc_fd;
}	t_comd;

//parsing

//environement
void	free_env_list(t_env *head);
t_env	*fill_env_list(char **env);
char	**put_list_in_array(t_env *lst_env);
t_env	*create_env_node(char *key, char *value);
void	split_env_line(char *str, char **key, char **value);
void	append_env_node(t_env **head, char *key, char *value);

// linked list
int		check_start_end(t_list *curr);
t_list	*create_list_node(char *cmd, t_type type);
void	add_back(t_list **head, char *cmd, t_type type);

// token
int		quotes(char c);
int		is_space(char c);
int		is_var_char(char c);
int		magic_character(char c);
void	handle_spc(int *i, char *str);
int		extract_var(int j, char *str);
int		skip_escape(int j, char *str);
int		extract_normal_char(char *str, int j);
char	*extract_string(int start, int j, char *str);
void	handle_magic_charc(int *i, char *str, t_list **tokens);

// syntax error
int		pipe_error(t_list *cmds);
int		syntax_error(t_list *cmds);
int		is_redirection(t_type token_type);

//environment

// tokens to commands
t_comd	*init_cmds(void);
int		is_escaped_char(char c);
void	clear_list(t_list **head);
void	init_new_cmd(t_comd **curr);
int		check_start_end(t_list *curr);
void	handle_spc(int *i, char *str);
char	*handle_char(int *i, char *str);
char	*handle_slash(int *i, char *str);
void	fill_args(t_comd *curr, t_list **token);
int		count_quotes(t_list *cmds, char quote_type);
void	handle_output_append(t_comd *curr, t_list **token);
void	handle_input_redirect(t_comd *curr, t_list **token);
void	handle_output_redirect(t_comd *curr, t_list **token);

#endif