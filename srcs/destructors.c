/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:56:02 by terabu            #+#    #+#             */
/*   Updated: 2023/04/29 16:17:50 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token(t_token *tok)
{
	if (tok)
		free_token(tok->next);
	else
		return ;
	if (tok->word)
		free(tok->word);
	free(tok);
}

void	free_nodelist(t_node *node)
{
	if (node == NULL)
		return ;
	free_token(node->args);
	free_token(node->filename);
	free_nodelist(node->redirects);
	free_nodelist(node->next);
	free(node);
}
