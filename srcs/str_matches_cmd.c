/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_matches_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:23:59 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/21 11:19:47 by terabu           ###   ########.fr       */
/*                           w                                                 */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	line_matches_cmd(char *line,t_environ *environ)
{
	t_token	*token;
	t_node	*node;

	token = tokenize(line);
	if (syntax_error)
		return ;
	node = parse(token);
	expand(node);
	execution(node,environ);
	return ;
}
