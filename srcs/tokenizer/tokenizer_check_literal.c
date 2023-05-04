/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_check_literal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:50:42 by terabu            #+#    #+#             */
/*   Updated: 2023/04/27 13:46:33 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ブランクチェック
bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

// トークンとキーワードを比較
bool	is_keyword(const char *s, const char *keyword)
{
	return (ft_memcmp(s, keyword, ft_strlen(keyword)) == 0);
}

// リダイレクション文字のチェック
bool	is_redirection_operator(const char *s)
{
	static char *const	operators[] = {">", "<", ">>", "<<"};
	size_t				i;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (is_keyword(s, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

// メタキャラクタチェック
bool	is_metacharacter(char c)
{
	if (c && (c == '|' || c == '&' || c == ';' || c == '(' || c == ')'
			|| c == '<' || c == '>' || c == ' ' || c == '\t' || c == '\n'))
		return (true);
	else
		return (false);
}

// ワードチェック（メタキャラではないか）
bool	is_word(const char *s)
{
	return (*s && !is_metacharacter(*s));
}
