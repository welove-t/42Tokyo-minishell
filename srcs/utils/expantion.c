/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:39:04 by terabu            #+#    #+#             */
/*   Updated: 2023/04/23 16:28:05 by susasaki         ###   ########.fr       */
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

static void	last_exit_status(char **new_word)
{
	char	*str;

	//グローバル変数を代入して、char型に変えて代入
	str = ft_itoa(g_status);
	while (*str != '\0')
		append_char(new_word, *str++);
}

static void	expand_env(char **new_word, char *p)
{
	char	*value;
	char	*new;

	if (*p == '?')
	{
		last_exit_status(new_word);
		return ;
	}
	value = getenv(p);
	if (value == NULL)
	{
		new = malloc(1);
		new[0] = '\0';
		*new_word = new;
		free(new);
		return ;
	}
	while (*value != '\0')
		append_char(new_word, *value++);
	return ;
}

void	handle_dollar_sign(char **p, char **exp_tmp)
{
	if (*((*p) + 1) == ' ' || *((*p) + 1) == '\t' || *((*p)
			+ 1) == '\0')
	{
		return;
	}
	else
	{
		(*p)++;
		if (**p == '?')
			append_char(exp_tmp, *((*p)++));
		else
		{
			while (**p && !is_metacharacter(**p) && **p != '\"'
				&& **p != '\'')
				append_char(exp_tmp, *((*p)++));
		}
	}
}

void	dollar_sign(char **p, char **new_word)
{
	char	*exp_tmp;

	exp_tmp = NULL;
	while (**p && !is_metacharacter(**p) && **p != '\"' && **p != '\'')
	{
		if (**p == DOLLAR_SIGN)
		{
			handle_dollar_sign(p, &exp_tmp);
			if (exp_tmp)
			{
				expand_env(new_word, exp_tmp);
				free(exp_tmp);
				exp_tmp = NULL;
			}
			else
			{
				append_char(new_word, *((*p)++));
				append_char(new_word, *((*p)++));
				break ;
			}
		}
		else
		{
			break ;
		}
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

	// char	*exp_tmp;
	if (tok == NULL || tok->kind != TK_WORD || tok->word == NULL)
		return ;
	p = tok->word;
	new_word = NULL;
	while (*p && !is_metacharacter(*p))
	{
		// printf("*p = %c\n",*p);
		if (*p == DOLLAR_SIGN)
		{
			dollar_sign(&p, &new_word);
			// break ;
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
			{
				if (*p == DOLLAR_SIGN)
					dollar_sign(&p, &new_word);
				else
					append_char(&new_word, *p++);
			}
			// skip quote
			p++;
		}
		else
			append_char(&new_word, *p++);
	}
	free(tok->word);
	tok->word = new_word;
	process_word_token(tok->next);
}

/*

*/
void	expand_quote_removal(t_node *node)
{
	if (node == NULL)
		return ;
	process_word_token(node->args);
	process_word_token(node->filename);
	expand_quote_removal(node->redirects);
	expand_quote_removal(node->next);
}

void	expand(t_node *node)
{
	expand_quote_removal(node);
}
