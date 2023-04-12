/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 09:43:47 by terabu            #+#    #+#             */
/*   Updated: 2023/04/12 10:19:38 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

bool	is_redirection_operator(const char *s)
{
	static char *const	operators[] = {">", "<", ">>", "<<"};
	size_t	i = 0;

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(s, operators[i]))
			return (true);
		i++;
	}
	return(false);
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
	// return (c && strchr("|&;()<>\t\n", c));
	if (c && (c == '|' || c == '&' || c == ';' || c == '(' || c == ')'
			|| c == '<' || c == '>' || c == ' ' || c == '\t' || c == '\n'))
			return(true);
	else
		return(false);
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
	static char	*const	operators[] = {">>", "<<", "||", "&", "&&", ";", ";;",
		">", "<", "(", ")", "|", "\n"};
	size_t				i = 0;
	char				*op;

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(line, operators[i]))
		{
			op = strdup(operators[i]);
			if (op == NULL)
				perror("strdup");
			*rest = line + strlen(op);
			return (new_token(op, TK_OP));
		}
		i++;
	}
	assert_error("Unexpected operator");
	exit(1);
}

t_token	*word(char **rest, char *line)
{
	const char	*start = line;
	char		*word;

	while (*line && !is_metacharacter(*line))
	{
		// single_quoteが閉じているかチェック
		if (*line == SINGLE_QUOTE_CHAR)
		{
			line++;
			while (*line && *line != SINGLE_QUOTE_CHAR)
				line++;
			if (*line == '\0')
			{
				tokenize_error("Unclosed single quote", rest, line);
				break;
			}
			else
				line++;
		}
		else if (*line == DOUBLE_QUOTE_CHAR)
		{
			line++;
			while (*line && *line != DOUBLE_QUOTE_CHAR)
				line++;
			if (*line == '\0')
			{
				tokenize_error("Unclosed double quote", rest, line);
				break;
			}
			else
				line++;
		}
		else
			line++;
	}

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

	syntax_error = false;
	head.next = NULL;
	token = &head;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_metacharacter(*line))
			token = token->next = operator(&line, line);
		else if (is_word(line))
			token = token->next = word(&line, line);
		else
			tokenize_error("Unexpected Token", &line, line);
	}
	token->next = new_token(NULL, TK_EOF);
	return (head.next);
}

size_t get_token_count(t_token *token)
{
	size_t	count;
	t_token	*cursor;

	count = 0;
	cursor = token;
	while (cursor->word != NULL && cursor->kind != TK_EOF)
	{
		cursor = cursor->next;
		count++;
	}
	return (count);
}

char	**token_list_to_array(t_token *token)
{
	size_t	count;
	size_t	i;
	char	**tok_array;
	t_token	*cursor;

	count = get_token_count(token);
	tok_array = ft_calloc(count + 1, sizeof(char *));
	if (!tok_array)
		perror("calloc");
	cursor = token;
	i = 0;
	while(cursor->word != NULL && cursor->kind != TK_EOF)
	{
		tok_array[i] = ft_strdup(cursor->word);
		if (!tok_array[i])
			perror("strdup");
		i++;
		cursor = cursor->next;
	}
	tok_array[i] = NULL;
	return (tok_array);
}
