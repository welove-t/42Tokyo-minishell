/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:35:10 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/04 13:20:10 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/param.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../srcs/lib/libft/libft.h"

#define SINGLE_QUOTE_CHAR '\''
#define DOUBLE_QUOTE_CHAR '"'

extern char	**environ;

typedef struct s_token		t_token;
typedef enum e_token_kind	t_token_kind;

t_token	*new_token(char *word, t_token_kind kind);

// トークンの種類
enum e_token_kind {
	TK_WORD,	// ワード
	TK_RESERVED, // 記号
	TK_OP,		// 制御文字
	TK_EOF,		// 入力終わり
};
// `word` is zero terminated string.
struct s_token {
	char			*word;
	t_token_kind	kind;
	t_token			*next;
};

//main.c

//line_matches_cmd.c
void line_matches_cmd(char *line);

//buliin
//echo.c
void bi_echo(char *str);

//pwd.c
int bi_pwd(void);

// utils
char	*get_cmd_array(char *cmd_line);

// tokenizer
t_token	*tokenize(char *line);
char	**token_list_to_array(t_token *token);
bool	is_metacharacter(char c);

// expantion
void	expand(t_token *tok);

#endif
