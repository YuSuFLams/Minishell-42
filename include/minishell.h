/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:05:17 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/10/15 18:32:51 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <curses.h>
# include <limits.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <ctype.h>
# include "parsing.h"

# define SPATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# define ERRSYN "Minishell: syntax error near unexpected token `"

# define ERROR		-1
# define ERR_GETCWD "cd: error retrieving current directory: getcwd: cannot \
access parent directories: "
# define MESSAGE_COR "\033[1;36mminishell\033[0m (\033[32m0\033[0m)$ \033[0m"
# define MESSAGE_FAL "\033[1;36mminishell\033[0m (\033[31m1\033[0m)$ \033[0m"
# define WELCOME  "\n \
	\033[1;34m╔══════════════════════════════════════════════════════════════════════════════════╗\033[34m\n\
	\033[1;34m║\033[34m   \033[1;31m███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗  ███████╗ ██║      ██║      \033[34m  \033[1;34m║\033[34m\n\
	\033[1;34m║\033[34m   \033[1;31m████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║  ██╔════╝ ██║      ██║        \033[34m\033[1;34m║\033[34m\n\
	\033[1;34m║\033[34m   \033[1;31m██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║  █████╗   ██║      ██║        \033[34m\033[1;34m║\033[34m\n\
	\033[1;34m║\033[34m   \033[1;31m██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║  ██╔══╝   ██║      ██║        \033[34m\033[1;34m║\033[34m\n\
	\033[1;34m║\033[34m   \033[1;31m██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║  ███████╗ ███████╗ ███████╗   \033[34m\033[1;34m║\033[34m\n\
	\033[1;34m║\033[34m   \033[1;31m╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝  ╚══════╝ ╚══════╝ ╚══════╝   \033[34m\033[1;34m║\033[34m\n\
	\033[1;34m╚═══════════════════════════════════════════════════\
═══════════════════════════════╝\033[34m\n"

int	g_exit_cmd;

typedef struct s_shell
{
	bool			test_her; 
	char			*cp;
	bool			test;
	char			**str;
	char			*_pwd;
	char			*path;
	char			**cmnd;
	char			*_oldpwd;
	char			*path_all;
	int				flag;
	char			*home;
	t_list			*cmd_list;
	t_comd			*allcmnd;
	char			input_err;
	struct s_shell	*next;
}			t_shell;

// Minishell Fonction

//-->Utils of Minishell
char			*ft_itoa(int n);
int				count_nbr(int n);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_isdigit(int c);
int				is_all_digit(char *s);
int				set_size_arg(char **s);
bool			empty_line(char *line);
t_list			*ft_lstnew(int content);
int				lst_size_cmd(t_env *lst);
t_list			*ft_lstlast(t_list *lst);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
void			freesplit(char **s, int i);
long long int	atoi_exit(const char *str);
void			ft_bzero(void *s, size_t n);
void			ft_putnbr_fd(int n, int fd);
int				count(char const *s, char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
int				ft_strcmp(char *s1, char *s2);
void			ft_putendl_fd(char *s, int fd);
char			*ft_strchr(const char *s, int c);
char			**ft_split(char const *s, char c);
char			*ft_strcat(char *dest, char *src);
char			*ft_strcpy(char *dest, char *src);
void			*ft_memset(void *s, int c, size_t n);
char			*ft_strstr(char *str, char *to_find);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strndup(const char *src, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_lstadd_back(t_list **lst, t_list *new_cmd);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
char			*ft_strncpy(char *dest, const char *src, unsigned int n);
char			*ft_substr(char const *s, unsigned int start, size_t len);

//->src

//-->parsing
//Tokens
int				is_space(char c);

//Signals Minishell
void			sig_ctlc(int input_sig);
void			sig_quit(int input_sig);

//utils Minishell
void			check_that(void);
char			*get_access(t_shell *cmd);
void			mini_shell_w(t_shell *cmd);
char			*print_minishell(char *input);
//-->builtins

//x:---> "export":
int				check_input(char *s);
char			*new_string(char *s);
int				check_valid_id(char c);
char			*extract_after_equal(char *s);
char			*extract_before_plus(char *s);
char			*remove_first_plus(char *str);
char			*extract_before_equal(char *s);
char			*remove_quotes(char *s, char c);
int				search_p_q(char *s, char d_quot);
int				check_char(t_shell *cmd, char *s);
int				search_plus(char *s, char d_quot);
char			*substring_before_equal(char *str);
void			test_export(t_shell *shell_m, int i);
char			*extra(char **s, int i, char *s_add);
int				find_first_equal_or_length(char *str);
void			if_qoute_exit(t_shell *shell, char *s);
bool			check_cmd_exp(t_shell *sh_m, char *cmd);
void			shell_export(t_shell *sh, t_comd *mini);
int				check_plus_equal(t_shell *cmd, char *s);
char			**add_var_export(char **shell, char *str);
void			test_err_ex(t_shell *shell_m, char *new_s);
int				find_cmd_exist_plus(char **s, char *sh_cmnd);
int				find_command(t_shell *shell_m, char *sh_cmnd);
char			**add_if_plus_exit(char **s, char *s_add, int len);
char			**put_array(char **arr, char **new_arr, char *str);
void			another_export(t_shell *shell_m, char *new_s, int i);
char			**loop_add_var(char **arr, char **new_arr, char *str);
void			add_cmnd(t_shell *shell_m, int len, int i, char **tmp);

//x:---> "cd":
int				findsubstring(char *str);
void			search_p_o_p(t_shell *cmd);
void			add_up_to_env(t_shell *m_shell);
char			*get_path(char **split, char *str);
char			*find_path(t_shell *mini_s, char *find);
void			change_path(t_shell *cmd, t_comd *mini);
bool			check_cd_arg(t_shell *cmd, t_comd *mini);
void			shell_cd(t_shell *shell_m, t_comd *mini);
int				check_way(char *cmd, t_shell *cm, t_comd *mini);

//x:---> "env":
char			*ft_strd(char *s, t_shell *sh_m);
void			shell_env(t_shell *cmd, t_comd *mini);
void			check_env_export(t_shell *cmd, char **s, t_comd *mini);

//x:---> "pwd":
void			shell_pwd(t_shell *cmd, t_comd *mini);

//x:---> "exit":
void			another_exit(char *s, t_comd *mini);
void			shell_exit(t_shell *cmd, t_comd *mini);
//x:---> "unset":
bool			check_cmnd_unset(char *s);
void			shell_unset(t_shell *sh_m);
char			**del_var(char *cmd, char **env);
bool			check_syntax_cmd(char *env, char *cmnd);
char			**loop_add_env(char *str, char **env, char **cmd);

//x:---> "echo":
bool			is_single_hyphen_n(char *s);
void			shell_echo(t_shell *cmd, t_comd *mini);

//utils builtinds
bool			test_home(t_shell *cmd);
void			sig_child(int input_sig);
char			**bubble_sort(char **str);
void			ft_swap(char **str1, char **str2);
char			**fill_input(t_comd *source, t_shell *cmd);

//-->executable

//expander_dollar
bool			aftre_do(int c);
char			*join_char(char c);
bool			aftre_do_1(char *s, int i);
char			*strjoin_another(char *s1, char *s2);
int				check_int_after_dol(char *s, int pos);
char			**expand_name(char **s, t_shell *cmd);
int				length_after_do(int pos_dol, char *s);
char			*set_if_do(t_shell *cmd, char *s, int i);
char			*another_after(char *tmp, char *s, int i);
char			**cpy_command_echo(t_shell *cmd, char **s);
char			*do_qeus(char *tmp, int len, char *tmp_str);
int				if_dollar_exist(t_shell *cmd, char *str, char **tmp, int j);

//execut_command
void			mini_exec(t_shell *m_sh, t_comd *parsed_cmd);

//error_minishell
void			print_errur_cd(char *s);
void			print_errur_exit(char *s);
void			command_not_found(char *s);
void			err_in_dir(DIR *dir, char *str);
int				export_unset_err(char *cmd, char *s);

//Syntex_errur
void			all_signals(void);
int				size_cmd(t_comd *lst);
bool			is_builten(t_comd *msh);
bool			check_qoutes(char *input, t_shell *cmnd);
char			*get_path_acc(t_shell *mini, t_comd *cmd);
void			execute_built(t_shell *m_sh, t_comd *mini);
bool			check_syntex_input(char *input, t_shell *cmd);
char			*handle_quotes(t_shell *cmd, int *i, char *str);
void			one_command(t_shell *cmd, t_comd *mini, char *s);
void			execute_another_command(t_shell *shell, t_comd *cmd);
char			*handle_double_quote(t_shell *m_sh, int *i, char *str);
char			*extract_var_content(t_shell *m_sh, int *j, char *str);
int				tokenisation(t_shell *m_sh, char *input, t_list **tokens);
bool			parse_command(t_shell *m_sh, char *input, t_list **tokens, \
t_comd **parsed_cmd);
void			handle_word(t_shell *m_sh, int *i, char *str, t_list **tokens);

// last version
void			signal_def(void);
int				size_cmd(t_comd *lst);
void			close_fd_open(t_comd *cmd);
void			close_all_fd(t_comd *cmd, int **fd);
char			*expander_cmd(char *str, t_shell *cmd);
int				handle_heredoc(char *del, t_shell *mini);
int				handle_heredoc(char *del, t_shell *mini);
void			failed_execve(char *path, t_shell *lines);
int				heredoc_case(t_list *tokens, t_shell *mini);
void			set_command(t_shell *mini, t_comd *cmd, char *s);
char			*handle_dollar(t_shell *m_sh, int *i, char *str);
void			dup_com_pos(t_comd *cmd, int **fd, int i, int flag);
void			execute_another_command(t_shell *shell, t_comd *cmd);
void			first_cmd(t_shell *mini, t_comd *cmd, int **fd, int *i);
void			last_command(t_shell *mini, t_comd *cmd, int **fd, int *i);
void			handle_her_red(t_comd *curr, t_list **token, t_shell *mini);
void			comand_between(t_shell *mini, t_comd *cmd, int **fd, int *i);
void			handle_append_token(t_comd *command, t_list **tokens, \
t_list *tmp);
void			handle_special_tokens(t_comd *command, t_list **tokens, \
t_shell *mini, t_list *tmp);

#endif
