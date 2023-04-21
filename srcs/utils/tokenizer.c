/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 09:43:47 by terabu            #+#    #+#             */
/*   Updated: 2023/04/21 11:20:47 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*word(char **rest, char *line);
static t_token	*operator(char **rest, char *line);

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

	syntax_error = false;
	head.next = NULL;
	token = &head;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_metacharacter(*line))
		{
			token->next = operator(&line, line);
			token = token->next;
		}
		else if (is_word(line))
		{
			token->next = word(&line, line);
			token = token->next;
		}
		else
			tokenize_error("Unexpected Token", &line, line);
	}
	token->next = new_token(NULL, TK_EOF);
	return (head.next);
}

// 新しいトークンの作成
t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*tok;

	tok = calloc(1, sizeof(*tok));
	if (tok == NULL)
		perror("calloc");
	tok->word = word;
	tok->kind = kind;
	return (tok);
}

// 制御文字のトークン作成
static t_token	*operator(char **rest, char *line)
{
	static char *const	operators[] = {">>", "<<", "||", "&", "&&", ";", ";;",
		">", "<", "(", ")", "|", "\n"};
	size_t				i;
	char				*op;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (is_keyword(line, operators[i]))
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
	exit(1);
}

static t_token	*word(char **rest, char *line)
{
	const char	*start = line;
	char		*word;
	int			quote_err_flg;

	quote_err_flg = 0;
	quote_err_flg = check_quote(&line);
	if (quote_err_flg == -1)
		tokenize_error("Unclosed single quote", rest, line);
	if (quote_err_flg == -2)
		tokenize_error("Unclosed double quote", rest, line);
	// printf("%s\n", line);
	word = strndup(start, line - start);
	if (word == NULL)
		fatal_error("strndup");
	*rest = line;
	return (new_token(word, TK_WORD));
}
