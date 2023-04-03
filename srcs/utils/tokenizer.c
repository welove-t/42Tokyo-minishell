/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 09:43:47 by terabu            #+#    #+#             */
/*   Updated: 2023/04/03 10:31:10 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

// 新しいトークンの作成
t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*tok;

	tok = calloc(1, sizeof(*tok));
	if (tok == NULL)
		fatal_error("calloc");
	tok->word = word;
	tok->kind = kind;
	return (tok);
}

// ブランクだったらtrue
bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

// lineの先頭ブランクを飛ばして、lineを更新
// ブランクだったらtrue、ブランクでなければfalse
bool	consume_blank(char **rest, char *line)
{
	if (is_blank(*line))
	{
		while (*line && is_blank(*line))
			line++;
		*rest = line;
		return (true);
	}
	*rest = line;
	return (false);
}

// トークンとキーワードを比較
bool	startswith(const char *s, const char *keyword)
{
	return (memcmp(s, keyword, strlen(keyword)) == 0);
}

/*
metacharacter
	  A character that, when unquoted, separates words.  One of the following:
	  |  & ; ( ) < > space tab
control operator
	  A token that performs a control function.  It is one of the following symbols:
	  || & && ; ;; ( ) | <newline>
*/

// 制御演算子チェック
// 制御演算子だったらtrue
bool	is_operator(const char *s)
{
	static char	*const operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t				i = 0;

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(s, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

/*
DEFINITIONS
       The following definitions are used throughout the rest of this document.
       blank  A space or tab.
       word   A sequence of characters considered as a single unit by the shell.  Also known as a token.
       name   A word consisting only of alphanumeric characters and underscores, and beginning with an alphabetic
              character or an underscore.  Also referred to as an identifier.
       metacharacter
              A character that, when unquoted, separates words.  One of the following:
              |  & ; ( ) < > space tab
       control operator
              A token that performs a control function.  It is one of the following symbols:
              || & && ; ;; ( ) | <newline>
*/
// メタキャラクタチェック
// メタキャラクタだったらtrue
bool	is_metacharacter(char c)
{
	return (c && strchr("|&;()<> \t\n", c));
}

// ワードチェック
// メタキャラクタでなければtrue
bool	is_word(const char *s)
{
	return (*s && !is_metacharacter(*s));
}

// 制御文字のトークン作成
t_token	*operator(char **rest, char *line)
{
	static char	*const	operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t				i = 0;
	char				*op;

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(line, operators[i]))
		{
			op = strdup(operators[i]);
			if (op == NULL)
				fatal_error("strdup");
			*rest = line + strlen(op);
			return (new_token(op, TK_OP));
		}
		i++;
	}
	assert_error("Unexpected operator");
}

t_token	*word(char **rest, char *line)
{
	const char	*start = line;
	char		*word;

	while (*line && !is_metacharacter(*line))
		line++;
	word = strndup(start, line - start);
	if (word == NULL)
		fatal_error("strndup");
	*rest = line;
	return (new_token(word, TK_WORD));
}

/*
lineのトークン化
headは空のトークン
tokはheadのアドレスを指す
	→トークンリストは最初の要素としてheadを持つことができる

-----------------------------------------------------
例：line = ls -al | grep main.c
「ls」「-al」「|」「grep」「main.c」の順に、t_token型の要素が繋がったリストがhead.nextに入る。
具体的には、
head.next->wordは「ls」、
head.next->kindはTK_WORD、
-
head.next->next->wordは「-al」、
head.next->next->kindはTK_WORD、
-
head.next->next->next->wordは「|」、
head.next->next->next->kindはTK_OP、
-
head.next->next->next->next->wordは「grep」、
head.next->next->next->next->kindはTK_WORD、
-
head.next->next->next->next->next->wordは「main.c」、
head.next->next->next->next->next->kindはTK_WORD
となる。

*/


t_token	*tokenize(char *line)
{
	t_token	head;
	t_token	*token;

	head.next = NULL;
	token = &head;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_operator(line))
			token = token->next = operator(&line, line);
		else if (is_word(line))
			token = token->next = word(&line, line);
		else
			assert_error("Unexpected Token");
	}
	token->next = new_token(NULL, TK_EOF);
	return (head.next);
}
