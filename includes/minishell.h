/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:35:10 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/01 14:47:32 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../srcs/lib/libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'
# define ERROR_PREFIX "minishell: "
# define DOLLAR_SIGN '$'
# define SIG_GET 100
# define SIG_SET 200

extern char					**environ;

typedef struct s_token		t_token;
typedef struct s_node		t_node;
typedef enum e_token_kind	t_token_kind;
typedef enum e_node_kind	t_node_kind;
typedef struct stat			t_stat;
typedef struct s_global		t_global;
t_global					g_global;

t_token						*new_token(char *word, t_token_kind kind);

// グローバル変数の構造体
struct						s_global
{
	bool					syntax_error;
	int						status;
	int						flg_redir;
};
// トークンの種類
enum						e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
};

// ノードの種類
enum						e_node_kind
{
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC,
};

// ノード
struct						s_node
{
	t_node_kind				kind;
	t_node					*next;
	t_node					*prev;
	t_token					*args;
	t_node					*redirects;
	int						target_fd;
	t_token					*filename;
	t_token					*delimiter;
	int						file_fd;
	int						stacktmp_fd;
	pid_t					pid;
	int						pfd[2];
};
// `word` is zero terminated string.
struct						s_token
{
	char					*word;
	t_token_kind			kind;
	t_token					*next;
};

typedef struct s_environ
{
	char					*name;
	char					*value;
	struct s_environ		*next;
}							t_environ;

//main.c

//line_matches_cmd.c
void						line_matches_cmd(char *line, t_environ *environ);

// init_environ_list
int							first_strlen(char *str);
int							latter_strlen(char *str);
t_environ					*init_environ_list(void);

// ------------------------------------------------
// builtin
// ------------------------------------------------

//cd.c
int							bi_cd(char **argv, int argc);

//echo.c
int							bi_echo(char **argv);

//env.c
int							bi_env(int argc, t_environ *environ);

//pwd.c
int							bi_pwd(void);

//exit.c
int							bi_exit(char **argv);

//export_utils.c
void						environ_nodeadd_back(t_environ *env,
								t_environ *new);
t_environ					*environ_node_new(char *name, char *value);

//export.c
char						*make_name(char *str);
char						*make_value(char *str);
void						bi_only_export_env(t_environ *env);
int32_t						bi_export(t_environ *env, char **argv, int argc);

// unset.c
int							bi_unset(t_environ *environ, char **argv, int argc);
t_environ					*find_variable(t_environ *environ, char *str);

int							search_bi_cmd(t_node *node, t_environ *environ);

// utils
char						*get_cmd_array(char *cmd_line);

// ------------------------------------------------
// tokenizer
// ------------------------------------------------

// tokenizer-main
t_token						*tokenize(char *line);
t_token						*new_token(char *word, t_token_kind kind);

// tokenizer-check-literal
bool						is_blank(char c);
bool						is_keyword(const char *s, const char *keyword);
bool						is_redirection_operator(const char *s);
bool						is_metacharacter(char c);
bool						is_word(const char *s);

//heredoc
void						do_heredoc(t_node *redir);
void						delete_heredoc(void);

// tokenizer-check-quote
int							check_quote(char **line);
bool						consume_single_quote(char **line);
bool						consume_double_quote(char **line);

// tokenizer-utils
size_t						get_token_count(t_token *token);
char						**token_list_to_array(t_token *token);
bool						consume_blank(char **rest, char *line);
bool						consume_double_quote(char **line);

// ------------------------------------------------
// Parser
// ------------------------------------------------

// parser-main
t_node						*parse(t_token *tok);
t_node						*new_node(t_node_kind kind, t_node *prev);
void						append_node(t_node **node, t_node *elm);
void						append_command_element(t_node *command,
								t_token **rest,
								t_token *tok);
bool						is_operator(t_token *tok, char *op);

// parser-make-tok
t_token						*tokdup(t_token *tok);
void						append_tok(t_token **tokens, t_token *tok);

// parser-node-redirect
t_node						*redirect_out(t_token **rest, t_token *tok);
t_node						*redirect_in(t_token **rest, t_token *tok);
t_node						*redirect_append(t_token **rest, t_token *tok);
t_node						*redirect_heredoc(t_token **rest, t_token *tok);

// parser-check
bool						parser_check_pipe(t_node *node, t_token *tok);

//heredoc
void						do_heredoc(t_node *redir);

// expantion
void						expand(t_node *node);

// dollar_sign
void						dollar_sign(char **p, char **new_word);

// process_word
void						append_char(char **s, char c);
void						process_word_token(t_token *tok);

// ------------------------------------------------
// recirection
// ------------------------------------------------

// redirect
void						redirection(t_node *redir);
void						open_redir_file(t_node *redir);
void						do_redirect(t_node *redir);
void						reset_redirect(t_node *redir);
int							do_open_redir_out(char *filepath);
int							do_open_redir_in(char *filepath);
int							do_open_redir_append(char *filepath);

// exec
void						exec_cmd(t_node *node);
void						execution(t_node *node, t_environ *environ);
size_t						get_node_cnt(t_node *node);

// ------------------------------------------------
// signal
// ------------------------------------------------
void						signal_c_cmd(void);
void						signal_backslash(void);
void						signal_handler(int sig);
int							signal_setget_status(int style, int sig);
void						signal_handler_heredoc(int sig);
void						signal_handler_waiting_input(int sig);

// ------------------------------------------------
// pipe
// ------------------------------------------------
void						pipex(t_node *node, size_t cnt_node,
								t_environ *environ);
void						waitpid_pipex(t_node *node, int *wstatus);
void						pipex_utils(t_node *node, int flag);

// ------------------------------------------------
// Error
// ------------------------------------------------
void						perror_prefix(void);
void						fatal_error(char *msg);
void						assert_error(char *msg);
void						err_exit(char *location, char *msg, int status);
void						tokenize_error(char *location, char **rest,
								char *line, int flg);
void						parse_error(t_token **rest, t_token *tok);
void						xperror(const char *location);
void						error_cmd(char *cmd);
void						put_error_msg(char *error_msg);
void						put_error_msg_endl(char *error_msg);
void						put_error_char(char c);
void						error_file(char *filename);
void						error_dir(char *dir);
void						error_exit(char *cmd);

// ------------------------------------------------
// Destructors
// ------------------------------------------------

void						finalize(int wstatus);
void						free_token(t_token *tok);
void						free_nodelist(t_node *node);
void						free_argv(char **args);
void						set_wstatus(int wstatus);

// ------------------------------------------------
// WRAPPER FUNCTION
// ------------------------------------------------
void						do_close(int fd);
void						do_write(int fd, const void *buf, size_t count);
void						do_dup2(int oldfd, int newfd);
void						do_pipe(int pipefd[2]);

#endif
