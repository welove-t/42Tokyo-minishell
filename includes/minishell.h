/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:35:10 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/21 11:04:41 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/param.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../srcs/lib/libft/libft.h"

#define SINGLE_QUOTE_CHAR '\''
#define DOUBLE_QUOTE_CHAR '"'
#define DOLLAR_SIGN '$'

extern char	**environ;
bool		syntax_error;
extern bool	g_syntax_error;
int			g_status;


typedef struct s_token		t_token;
typedef struct s_node		t_node;
typedef enum e_token_kind	t_token_kind;
typedef enum e_node_kind	t_node_kind;

t_token	*new_token(char *word, t_token_kind kind);

// トークンの種類
enum e_token_kind {
	TK_WORD,	// ワード
	TK_RESERVED, // 記号
	TK_OP,		// 制御文字
	TK_EOF,		// 入力終わり
};

// ノードの種類
enum e_node_kind {
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,	//>
	ND_REDIR_IN,	//<
	ND_REDIR_APPEND,//>>
	ND_REDIR_HEREDOC,//<<
};

// ノード
struct s_node {
	t_node_kind	kind;
	t_node		*next;
	t_node		*prev;
	//CMD
	t_token		*args;
	t_node		*redirects;
	//REDIR
	int			targetfd;
	t_token		*filename;
	t_token		*delimiter;
	int			filefd;
	int			stashed_targetfd;
	//pipe
	pid_t		pid;
	int			pfd[2];

};
// `word` is zero terminated string.
struct s_token {
	char			*word;
	t_token_kind	kind;
	t_token			*next;
};

typedef struct s_environ
{
	char			*name;
	char 			*value;
	struct s_environ *next;
}	t_environ;

typedef struct s_envinfo
{
	//先頭ノード
	t_environ *head;
}	t_envinfo;

//main.c

//line_matches_cmd.c
void		line_matches_cmd(char *line);

// init_environ_list
int			first_strlen(char *str);
int			latter_strlen(char *str);
t_environ	*init_environ_list();

//buliin
//echo.c
void	bi_echo(char *str);

//env.c
void	bi_env(t_environ *environ);

//pwd.c
int		bi_pwd(void);

//export_utils.c
void		environ_nodeadd_back(t_environ *env, t_environ *new);
t_environ *environ_node_new(char *name, char *value);

//export.c
char	*make_name(char *str);
char	*make_value(char *str);
void	bi_only_export_env(t_environ *env);
void	bi_export(t_environ *env, char *str);

// unset.c
void	bi_unset(t_environ *environ, char *str);

// utils
char	*get_cmd_array(char *cmd_line);

// ------------------------------------------------
// tokenizer
// ------------------------------------------------

// tokenizer-main
t_token	*tokenize(char *line);
t_token	*new_token(char *word, t_token_kind kind);

// tokenizer-check-literal
bool	is_blank(char c);
bool	is_keyword(const char *s, const char *keyword);
bool	is_redirection_operator(const char *s);
bool	is_metacharacter(char c);
bool	is_word(const char *s);

// tokenizer-check-quote
int		check_quote(char **line);
bool	consume_single_quote(char **line);
bool	consume_double_quote(char **line);

// tokenizer-utils
size_t	get_token_count(t_token *token);
char	**token_list_to_array(t_token *token);
bool	consume_blank(char **rest, char *line);
bool	consume_double_quote(char **line);

// ------------------------------------------------
// Parser
// ------------------------------------------------

// parser-main
t_node	*parse(t_token *tok);
t_node	*new_node(t_node_kind kind, t_node *prev);
void	append_node(t_node **node, t_node *elm);
void	append_command_element(t_node *command, t_token **rest, t_token *tok);
bool	is_operator(t_token *tok, char *op);

// parser-make-tok
t_token	*tokdup(t_token *tok);
void	append_tok(t_token **tokens, t_token *tok);

// parser-node-redirect
t_node	*redirect_out(t_token **rest, t_token *tok);
t_node	*redirect_in(t_token **rest, t_token *tok);
t_node	*redirect_append(t_token **rest, t_token *tok);
t_node	*redirect_heredoc(t_token **rest, t_token *tok);

//heredoc
void	do_heredoc(t_node *redir);

// expantion
void	append_char(char **s, char c);
void	dollar_sign(char **p, char **new_word);
void	expand(t_node *node);

// redirect
void	open_redir_file(t_node *redir);
void	do_redirect(t_node *redir);
void	reset_redirect(t_node *redir);

// exec
void	exec_cmd(t_node *node);
void	execution(t_node *node);


// ------------------------------------------------
// Error
// ------------------------------------------------
void	perror_prefix(void);
void	fatal_error(const char *msg);
void	assert_error(const char *msg);
void	err_exit(const char *location, const char *msg, int status);
void	todo(const char *msg);
void	tokenize_error(const char *location, char **rest, char *line);
void	parse_error(const char *location, t_token **rest, t_token *tok);
void	xperror(const char *location);

// pipe
void	pipex(t_node *node, size_t cnt_node);
void	waitpid_pipex(t_node *node);

#endif
