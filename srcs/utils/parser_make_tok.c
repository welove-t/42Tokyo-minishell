/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make_tok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 08:52:41 by terabu            #+#    #+#             */
/*   Updated: 2023/04/23 14:37:57 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 与えられたトークンの複製
t_token	*tokdup(t_token *tok)
{
	char	*word;

	if (tok->word == NULL)
		return (new_token(NULL, tok->kind));
	word = ft_strdup(tok->word);
	if (word == NULL)
		perror("strdup");
	return (new_token(word, tok->kind));
}

// 与えられたトークンを末尾に追加
void	append_tok(t_token **tokens, t_token *tok)
{
	if (*tokens == NULL)
	{
		*tokens = tok;
		return ;
	}
	append_tok(&(*tokens)->next, tok);
}
