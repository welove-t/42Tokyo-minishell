/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:31:19 by terabu            #+#    #+#             */
/*   Updated: 2023/04/15 12:39:30 by terabu           ###   ########.fr       */
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

// ノードリスト(通常コマンド用)の作成
t_node	*parse(t_token *tok)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD);
	append_command_element(node, &tok, tok);
	while (tok && tok->kind != TK_EOF)
		append_command_element(node, &tok, tok);
	append_command_element(node, &tok, tok); //終端ノードにNULL追加
	return (node);
}

// ノードリスト(リダイレクト-アウト用)の作成
t_node	*redirect_out(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_OUT);
	node->filename = tokdup(tok->next);
	node->targetfd = STDOUT_FILENO;
	*rest = tok->next->next; //">"の次がwordなのでさらにその次のノードを設定
	return (node);
}

// ノードリスト(リダイレクト-イン用)の作成
t_node	*redirect_in(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_IN);
	node->filename = tokdup(tok->next);
	node->targetfd = STDIN_FILENO;
	*rest = tok->next->next; //"<"の次がwordなのでさらにその次のノードを設定
	return (node);
}

// ノードリスト(リダイレクト-アペンド用)の作成
t_node	*redirect_append(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_APPEND);
	node->filename = tokdup(tok->next);
	node->targetfd = STDOUT_FILENO;
	*rest = tok->next->next; //">>"の次がwordなのでさらにその次のノードを設定
	return (node);
}

// ノードリスト(リダイレクト-ヒアドキュ用)の作成
t_node	*redirect_heredoc(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_HEREDOC);
	node->delimiter = tokdup(tok->next);
	node->targetfd = STDIN_FILENO;
	*rest = tok->next->next; //"<"の次がwordなのでさらにその次のノードを設定
	return (node);
}

// 制御文字のチェック
bool	is_operator(t_token *tok, char *op)
{
	if (tok->kind != TK_OP)
		return (false);
	return (strcmp(tok->word, op) == 0);
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
	// append_tok(&command->args, tokdup(tok));
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
