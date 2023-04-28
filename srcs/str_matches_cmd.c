/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_matches_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:23:59 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/28 10:21:11 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	line_matches_cmd(char *line, t_environ *environ)
{
	t_token	*token;
	t_node	*node;

	token = tokenize(line);
	if (g_global.syntax_error)
		return ;
	node = parse(token);
	if (g_global.syntax_error)
		return ;
	expand(node);
	execution(node, environ);
	return ;
}
