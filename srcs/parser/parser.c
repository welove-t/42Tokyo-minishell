/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:31:19 by terabu            #+#    #+#             */
/*   Updated: 2023/05/04 17:51:35 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//リストの終端にノードを追加
static void	append_node(t_node **node, t_node *elm)
{
	if (*node == NULL)
	{
		*node = elm;
		return ;
	}
	append_node(&(*node)->next, elm);
}

// 制御文字のチェック
static bool	is_operator(t_token *tok, char *op)
{
	if (tok->kind != TK_OP)
		return (false);
	return (ft_strcmp(tok->word, op) == 0);
}

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
			if (!parser_check_pipe(node, tok))
				return (head);
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

	node = ft_calloc(1, sizeof(*node));
	if (node == NULL)
		fatal_error("calloc");
	node->kind = kind;
	node->prev = prev;
	return (node);
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
	{
		parse_error(rest, tok);
		return ;
	}
	*rest = tok;
}
