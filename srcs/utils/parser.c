/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:31:19 by terabu            #+#    #+#             */
/*   Updated: 2023/04/08 12:06:42 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// トークン種類を設定
t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = calloc(1, sizeof(*node));
	if (node == NULL)
		perror("calloc");
	node->kind = kind;
	return (node);
}

// 与えられたトークンの複製
t_token	*tokdup(t_token *tok)
{
	char	*word;

	if (tok->word == NULL)
		return (new_token(NULL, tok->kind));
	word = strdup(tok->word);
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

t_node	*parse(t_token *tok)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD);
	while (tok && tok->kind != TK_EOF)
	{
		if (tok->kind == TK_WORD)
			append_tok(&node->args, tokdup(tok));
		else
			printf("Implement parser");
		tok = tok->next;
	}
	append_tok(&node->args, tokdup(tok));
	return (node);
}
