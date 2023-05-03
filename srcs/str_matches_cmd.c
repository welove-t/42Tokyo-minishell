/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_matches_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:23:59 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/03 16:45:20 by terabu           ###   ########.fr       */
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
	expand(node, environ);
	check_heredoc(node, environ);
	if (g_global.flg_redir)
	{
		loop_node_delete_heredoc(node);
		free_nodelist(node);
		g_global.flg_redir = 0;
		return ;
	}
	execution(node, environ);
	free_nodelist(node);
	return ;
}
