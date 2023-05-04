/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:15:06 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/04 15:31:52 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_heredoc(char *filename)
{
	if (!access(filename, R_OK))
		do_unlink(filename);
}

void	loop_node_delete_heredoc(t_node *node)
{
	t_node	*tmp;

	if (node == NULL)
		return ;
	tmp = node;
	while (tmp)
	{
		if (tmp->kind == ND_REDIR_HEREDOC && tmp->filename)
			delete_heredoc(tmp->filename->word);
		tmp = tmp->redirects;
	}
	loop_node_delete_heredoc(node->next);
}
