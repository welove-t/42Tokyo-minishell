/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_matches_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:23:59 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/01 19:16:58 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	line_matches_cmd(char *line, t_environ *environ)
{
	t_token	*token;
	t_node	*node;

	token = tokenize(line);
	if (g_global.syntax_error)
	{
		free_token(token);
		return ;
	}
	node = parse(token);
	free_token(token);
	if (g_global.syntax_error)
	{
		free_nodelist(node);
		return ;
	}
	expand(node,environ);
	execution(node, environ);
	free_nodelist(node);
	return ;
}
