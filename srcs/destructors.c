/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:56:02 by terabu            #+#    #+#             */
/*   Updated: 2023/04/29 17:48:06 by susasaki         ###   ########.fr       */
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

void	free_argv(char **args)
{
	size_t	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
