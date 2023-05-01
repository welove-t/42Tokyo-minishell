/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:39:04 by terabu            #+#    #+#             */
/*   Updated: 2023/05/01 19:16:44 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_quote_removal(t_node *node,t_environ *env)
{
	if (node == NULL)
		return ;
	process_word_token(node->args,env);
	process_word_token(node->filename,env);
	expand_quote_removal(node->redirects, env);
	expand_quote_removal(node->next, env);
}

void	expand(t_node *node,t_environ *env)
{
	expand_quote_removal(node, env);
}
