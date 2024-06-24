/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:50:50 by asajid            #+#    #+#             */
/*   Updated: 2023/12/08 12:01:42 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef enum s_token
{
	PIPE = 2,
	OUTFILE = 3,
	INFILE = 4,
	APPEND = 5,
	HEREDOC = 6,
	NUL = 0,
}					t_token;

typedef struct s_keymap
{
	char			*key;
	char			*val;
	struct s_keymap	*next;
}					t_keymap;

typedef struct s_env
{
	t_keymap		*keymap;
}					t_env;

typedef struct s_export
{
	t_keymap		*keymap;
}					t_export;

typedef struct s_path
{
	char			*command;
	char			*env_path;
	char			**path;
	int				i;
	char			**split_cmd;
	char			*join_cmd;
}					t_path;

typedef struct s_redir
{
	int				indx;
	char			*str;
	t_token			token;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	int				id;
	t_redir			*redirs;
	t_env			*env;
	t_export		*exp;
	char			**argv;
	int				**pipes;
	int				*pipe_in;
	int				*pipe_out;
	int				*redir_fds;
	int				*heredoc;
	int				count_fds;
	int				fd_in;
	int				fd_out;

	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	int				exit_status;
	int				cmd_count;
	int				pipe_count;
	t_cmd			*cmd;

}					t_shell;

typedef struct sig_stat
{
	int				exit_status;
	int				heredoc_fd;
}					t_sig_stat;

extern t_sig_stat	g_sig;

typedef struct s_lexer
{
	int				i;
	char			*str;
	t_token			token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

typedef struct s_tools
{
	char			*args;
	t_lexer			*list;
	int				pipes;
	int				quotes;
	struct s_pipe	*pipe_node;
}					t_tools;

typedef struct s_parser_list
{
	t_lexer			*list;
	t_lexer			*redirection;
	int				red_num;
	struct s_tools	*tools;
}					t_parser_list;

// struct of pipex
typedef struct s_pipe
{
	int				i;
	char			**cmd;
	t_lexer			*redirection;
	int				red_num;
	struct s_pipe	*next;
}					t_pipe;

int					lexer(t_tools *tools);
int					parser(t_tools *tools);
int					count_quotes(t_tools *tools, t_env *env);
int					add_to_list(char *str, t_token token, t_lexer **old_list);
int					count_args(t_lexer *lexer_list);
t_lexer				*ft_new_node(char *str, int token);
void				ft_add_next_node(t_lexer *new_list, t_lexer **old_list);

void				ft_del_one_node(t_lexer **lst, int key);
void				print_list(t_tools *tools);
void				print_list2(t_parser_list *parser_list);
void				print_redirection_list(t_lexer *redirection_node);
void				ft_clear_list(t_lexer **list);
void				print_pipex_list(t_pipe *list);
char				*dollar_expander(char *input, t_env *env);
t_env				*get_env(char **env);
void				add_keymap(t_keymap **head, t_keymap *new_keymap);
void				free_keymap(t_keymap *keymap);
t_keymap			*create_keymap(const char *key, const char *val);
void				sigle(t_tools *tools, t_env *env);
char				**after_dollar(t_pipe *node, t_env *env);
void				minishell(t_tools *tools, t_env *env_data,
						t_export *exp_data);
t_redir				*copy_redirs(t_lexer *head_double);
char				**ft_copy_commands(char **tools);
void				print_redir_list(t_redir *redir);
void				print_pipe_node(t_pipe *pipe);
void				fill_struct(t_shell *shell, t_pipe *pipe, t_env *env,
						t_export *exp);
char				*remove_quotes(char *input);
void				free_double(char **str);
int					count_str(char **str);

// pipe_node
t_pipe				*ft_new_pipe_node(char **str, int red_num,
						t_lexer *redirection);
void				ft_add_next_pipe_node(t_pipe **lst, t_pipe *new);
t_parser_list		ft_parser_node(t_tools *tools);

// error_check
void				parser_error(int error, t_tools *tools);
int					ft_token_error(t_tools *tools);
int					ft_error(t_tools *tools, int error);

// parser_utils
void				ft_count_pipes(t_lexer *list, t_tools *tools);
int					count_args(t_lexer *lexer_list);

// expander_utils
int					count_str(char **str);
char				*dollar_qstn(void);
int					ft_check(char *end);

void				free_pipe_list(t_pipe **lst);
int					all_spaces(t_tools *tools);

/* ======================== executor ===================================== */

t_export			*get_export(t_env *env);
void				ft_env(t_env *env);

void				ft_cd(t_env *env, char *new_path);

void				ft_echo(char **argv);

void				ft_env(t_env *env);

int					ft_exit(t_cmd *cmd, char **argv);
void				ft_exit_child(t_cmd *cmd, char **argv);

unsigned long long	ft_atoull(const char *str);
int					ft_isnumber(unsigned long long num, const char *str);

void				clean_exit(t_cmd *cmd);
void				clean_child_exit(t_cmd *cmd);
void				free_cmd(t_cmd *cmd);
void				panic(char *message, int status, char **argv);
void				panic_child(char *message, int status, t_cmd *cmd);

void				ft_export(t_env *env, t_export *export, char **argv);

void				get_pwd(t_env *env);

void				ft_unset(t_env *env, t_export *exp, char **argv);

int					is_new_line_only(char *buffer);
int					fill_heredoc(int *heredoc, char *limiter);
int					*add_heredoc(char *limiter);

int					handle_input(t_redir *redirs, int **heredoc, t_redir **temp,
						int *fd_in);
int					process_input(t_redir *redirs, int last_fd);
int					check_outputmode(t_redir *redir);
int					process_output(t_redir *redirs, int last_fd);

void				run_parent_redircmd(t_cmd *cmd, int fd_in, int fd_out);
void				redir_child(t_cmd *cmd, int fd_in, int fd_out);
void				run_redir_cmd(t_cmd *cmd, int fd_in, int fd_out);

void				pipe_child(t_cmd *cmd, int pipe_count, t_cmd *head);
int					handle_pipe_child(t_shell *shell, int **pipes);
void				run_pipex(t_shell *shell);

int					**make_pipes(int pipes, int fd_in, int fd_out);
void				assign_redir_fds(t_shell *shell, int *redirs, int counter);
int					set_io(t_shell *shell);
void				pipe_commands(t_shell *shell, int **pipes);

void				close_fds(int fd_in, int fd_out);
void				close_redir_fds(t_cmd *cmd);
void				free_redir_fds(t_cmd *cmd);

int					is_builtin(t_cmd *cmd);
int					parent_builtin(t_cmd *cmd);

int					verify_key(char *str);
void				ft_swap(t_keymap *a, t_keymap *b);
void				sort_export(t_keymap *keymap);
void				print_export(t_keymap *keymap);

t_keymap			*find_key(t_keymap *head, char *key);
void				add_env(t_keymap **head, char *key, char *val);
void				update_or_add_keymap(t_keymap **head, char *key, char *val);

void				free_env(t_env *env);
void				free_export(t_export *exp);

void				clean_parent(t_cmd *cmd);
void				ft_clean(t_cmd *cmd);

int					ft_strequals(char *s1, char *s2);
void				run_cmdline(t_shell *shell);
void				run_command(t_cmd *cmd, int fd_in, int fd_out);
void				run_childcommand(t_cmd *cmd, t_cmd *head);

int					search_path(t_env *env);
char				*get_path(t_env *env);
char				*find_path(char *command, t_env *env);

t_keymap			*find_key(t_keymap *head, char *key);

void				execute_cmd(t_cmd *cmd, char **argv, t_env *env);
void				child_execute(t_cmd *cmd, int fd_in, int fd_out);
void				ft_free(char **array);
void				free_all(char **s1, char **s2);
void				close_pipe_fd(int *pipe);
void				*free_pipes(int **pipes, int count);
void				get_exit_status(int status);
void				clear_redir_list(t_redir **redir_head);

void				fill_shell(t_shell *shell, t_cmd *cmd);
void				fill_struct(t_shell *shell, t_pipe *pipe, t_env *env,
						t_export *exp);

void				ctrl_c(int sig);
void				define_input_signals(void);

void				rl_replace_line(const char *text, int clear_undo);
#endif
