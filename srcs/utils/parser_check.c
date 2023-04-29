/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:31:19 by terabu            #+#    #+#             */
/*   Updated: 2023/04/29 11:44:09 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	parser_check_pipe(t_node *node, t_token *tok)
{
	t_token	*tmp;

	if (node->args == NULL || tok->next->kind != TK_WORD)
	{
		parse_error(&tok, tok);
		return (false);
	}
	tmp = node->args;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->kind != TK_WORD)
	{
		parse_error(&tok, tok);
		return (false);
	}
	return (true);
}
