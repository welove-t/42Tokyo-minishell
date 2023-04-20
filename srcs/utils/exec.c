/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:38:03 by terabu            #+#    #+#             */
/*   Updated: 2023/04/20 11:18:32 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// #define DB

size_t	get_node_cnt(t_node *node);

void	execution(t_node *node)
{
	size_t	cnt_node;

	cnt_node = get_node_cnt(node);
	if (cnt_node <= 1)
		exec_cmd(node);
	else
	{
		pipex(node, cnt_node);
		waitpid_pipex(node);
	}
}

void	exec_cmd(t_node *node)
{
	char	**cmd_line = NULL;

	open_redir_file(node->redirects);
	do_redirect(node->redirects);
	#ifdef DB
	printf();
	#endif
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

size_t	get_node_cnt(t_node *node)
{
	size_t	cnt;

	cnt = 0;
	while (node != NULL)
	{
		cnt++;
		node = node->next;
	}
	return (cnt);
}
