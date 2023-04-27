/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:38:25 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/27 15:12:26 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
quoteを除いたwordを1文字ずつ追加
------------------------------
例えばlineが「abcd」の場合、
1回目：初期値のnew(*s)はNULL、cは「a」、処理後のnew(*s)は「a\0」
2回目：初期値のnew(*s)は「a」、cは「b」、処理後のnew(*s)は「ab\0」
3回目：初期値のnew(*s)は「ab」、cは「c」、処理後のnew(*s)は「abc\0」
4回目：初期値のnew(*s)は「aabc」、cは「d」、処理後のnew(*s)は「abcd\0」
となる
------------------------------
*/

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += ft_strlen(*s);
	new = malloc(size);
	if (new == NULL)
		fatal_error("malloc");
	if (*s)
		strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

static void	process_quotes(char **p, char quote_char, char **new_word)
{
	(*p)++;
	while (**p != quote_char)
	{
		if (**p == DOLLAR_SIGN && *((*p) + 1) != '\0' && *((*p) + 1) != '\t'
			&& *((*p) + 1) != ' ' && quote_char == DOUBLE_QUOTE_CHAR)
			dollar_sign(p, new_word);
		else
			append_char(new_word, *(*p)++);
	}
	(*p)++;
}

static void	process_word_token_helper(char **p, char **new_word)
{
	while (**p && !is_metacharacter(**p))
	{
		if (**p == DOLLAR_SIGN && *((*p) + 1) != '\0')
			dollar_sign(p, new_word);
		else if (**p == SINGLE_QUOTE_CHAR)
			process_quotes(p, SINGLE_QUOTE_CHAR, new_word);
		else if (**p == DOUBLE_QUOTE_CHAR)
			process_quotes(p, DOUBLE_QUOTE_CHAR, new_word);
		else
			append_char(new_word, *(*p)++);
	}
}

/*
quoteを除外してtok->wordを更新する
quoteの開閉チェックはtokenizerで実施済みのため閉じられていることは保障されている
*/
void	process_word_token(t_token *tok)
{
	char	*new_word;
	char	*p;

	if (tok == NULL || tok->kind != TK_WORD || tok->word == NULL)
		return ;
	p = tok->word;
	new_word = NULL;
	process_word_token_helper(&p, &new_word);
	free(tok->word);
	tok->word = new_word;
	process_word_token(tok->next);
}
