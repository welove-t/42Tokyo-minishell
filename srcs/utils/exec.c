/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:38:03 by terabu            #+#    #+#             */
/*   Updated: 2023/04/19 11:21:56 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_node *node)
{
	char	**cmd_line = NULL;

	open_redir_file(node->redirects);
	do_redirect(node->redirects);
	cmd_line = token_list_to_array(node->args);
	cmd_line[0] = get_cmd_array(ft_strtrim(cmd_line[0], " "));
	if (cmd_line != NULL)
	{
		if (execve(cmd_line[0], cmd_line, environ) == -1)
		{
			// printf("\x1b[31mError: execve()\x1b[0m\n");
		}
		reset_redirect(node->redirects);
	}
}
