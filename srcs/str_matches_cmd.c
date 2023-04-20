/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_matches_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:23:59 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/20 10:51:45 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	line_matches_cmd(char *line)
{
	t_token	*token;
	t_node	*node;

	token = tokenize(line);
	node =	parse(token);
	expand(node);
	execution(node);
	// printf("%s\n", node->args->word);
	// printf("%s\n", node->args->next->word);
	// printf("%s\n", node->args->next->next->word);
	// open_redir_file(node->redirects);
	// do_redirect(node->redirects);
	// cmd_line = token_list_to_array(node->args);
	// cmd_line[0] = get_cmd_array(ft_strtrim(cmd_line[0], " "));
	// if (cmd_line != NULL)
	// {
	// 	if (execve(cmd_line[0], cmd_line, environ) == -1)
	// 	{
	// 		// printf("\x1b[31mError: execve()\x1b[0m\n");
	// 	}
	// 	reset_redirect(node->redirects);
	// }
	return ;
}
