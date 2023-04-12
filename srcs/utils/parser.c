/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:31:19 by terabu            #+#    #+#             */
/*   Updated: 2023/04/12 11:09:51 by terabu           ###   ########.fr       */
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
	append_command_element(node, &tok, tok);
	while (tok && tok->kind != TK_EOF)
		append_command_element(node, &tok, tok);
	append_command_element(node, &tok, tok);
	return (node);
}

//
t_node	*redirect_out(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_OUT);
	node->filename = tokdup(tok->next);
	node->targetfd = STDOUT_FILENO;
	*rest = tok->next->next; //">"の次がwordなのでさらにその次のノードに設定
	return (node);
}

bool	equal_op(t_token *tok, char *op)
{
	if (tok->kind != TK_OP)
		return (false);
	return (strcmp(tok->word, op) == 0);
}

//
void	append_command_element(t_node *command, t_token **rest, t_token *tok)
{
	if (tok->kind == TK_WORD)
	{
		append_tok(&command->args, tokdup(tok));
		tok = tok->next;
	}
	else if (equal_op(tok, ">") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_out(&tok, tok));
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

void	append_node(t_node **node, t_node *elm)
{
	if (*node == NULL)
	{
		*node = elm;
		return ;
	}
	append_node(&(*node)->next, elm);
}
