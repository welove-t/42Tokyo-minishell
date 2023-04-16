/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:39:04 by terabu            #+#    #+#             */
/*   Updated: 2023/04/16 14:53:19 by susasaki         ###   ########.fr       */
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
		size += strlen(*s);
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

static void expand_env(char **new_word,char *str)
{
	char *value;
	value = getenv(str);
	//環境変数の取得にgetenvを使う
	if (value == NULL)
	{
		printf("\n"); // 改行を出力して新しい行を開始
		append_char(new_word, '\0');
	}
	while (*value != '\0')
		append_char(new_word, *value++);
	// printf("new_word = %s\n",*new_word);
	// exit(0);
}

/*
quoteを除外してtok->wordを更新する
quoteの開閉チェックはtokenizerで実施済みのため閉じられていることは保障されている
*/
void remove_quote(t_token *tok)
{
	char	*new_word;
	char	*p;

	if (tok == NULL || tok->kind != TK_WORD || tok->word == NULL)
		return ;
	p = tok->word;
	new_word = NULL;
	//ドルマークだったら環境変数に飛んで展開する。
	//ここで呼ばれるのを前提にして関数を作成していく。
	//"と'は↑の処理が終わってからやる。
	//bashでパターンを分析する
	//echo "a$PATH b"
	//echo "a$PATHb"
	// printf("*p = %c\n",*p);
	while (*p && !is_metacharacter(*p))
	{
		if (*p == DOLLAR_SIGN)
		{
			p++;
			expand_env(&new_word, p);
		}
		else if (*p == SINGLE_QUOTE_CHAR)
		{
			p++;
			while (*p != SINGLE_QUOTE_CHAR)
				append_char(&new_word, *p++);
			// skip quote
			p++;
		}
		else if (*p == DOUBLE_QUOTE_CHAR)
		{
			// skip quote
			p++;
			while (*p != DOUBLE_QUOTE_CHAR)
				append_char(&new_word, *p++);
			// skip quote
			p++;
		}
		else
			append_char(&new_word, *p++);
	}
	free(tok->word);
	tok->word = new_word;
	remove_quote(tok->next);
}

/*

*/
void	expand_quote_removal(t_node *node)
{
	if (node == NULL)
		return ;
	remove_quote(node->args);
	remove_quote(node->filename);
	expand_quote_removal(node->redirects);
	expand_quote_removal(node->next);
}

void	expand(t_node *node)
{
	expand_quote_removal(node);
}
