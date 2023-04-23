/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:31:19 by terabu            #+#    #+#             */
/*   Updated: 2023/04/23 14:51:10 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ノードリスト(通常コマンド用)の作成
t_node	*parse(t_token *tok)
{
	t_node	*node;
	t_node	*head;

	node = new_node(ND_SIMPLE_CMD, NULL);
	head = node;
	while (tok && tok->kind != TK_EOF)
	{
		if (is_operator(tok, "|"))
		{
			append_tok(&node->args, new_token(NULL, TK_EOF));
			append_node(&node->next, new_node(ND_SIMPLE_CMD, node));
			node = node->next;
			tok = tok->next;
		}
		else
			append_command_element(node, &tok, tok);
	}
	append_command_element(node, &tok, tok);
	return (head);
}

// ノード作成（トークン種類ごと）
t_node	*new_node(t_node_kind kind, t_node *prev)
{
	t_node	*node;

	node = calloc(1, sizeof(*node));
	if (node == NULL)
		perror("calloc");
	node->kind = kind;
	node->prev = prev;
	return (node);
}

// 制御文字のチェック
bool	is_operator(t_token *tok, char *op)
{
	if (tok->kind != TK_OP)
		return (false);
	return (ft_strcmp(tok->word, op) == 0);
}

// トークンの種類ごとにノード追加
void	append_command_element(t_node *command, t_token **rest, t_token *tok)
{
	if (tok->kind == TK_WORD)
	{
		append_tok(&command->args, tokdup(tok));
		tok = tok->next;
	}
	else if (is_operator(tok, ">") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_out(&tok, tok));
	else if (is_operator(tok, "<") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_in(&tok, tok));
	else if (is_operator(tok, ">>") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_append(&tok, tok));
	else if (is_operator(tok, "<<") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_heredoc(&tok, tok));
	else if (tok->kind == TK_EOF)
	{
		append_tok(&command->args, tokdup(tok));
		tok = NULL;
	}
	else
		todo("Unexpected Token");
	*rest = tok;
}

//リストの終端にノードを追加
void	append_node(t_node **node, t_node *elm)
{
	if (*node == NULL)
	{
		*node = elm;
		return ;
	}
	append_node(&(*node)->next, elm);
}
