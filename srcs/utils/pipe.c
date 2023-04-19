/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:45:00 by terabu            #+#    #+#             */
/*   Updated: 2023/04/19 11:22:17 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	get_node_cnt(t_node *node);
void			output_pipe_dup_close(int fd[2]);
void			input_pipe_dup_close(int fd[2]);
void			close_pipe(t_node *node, t_node *head);

void	pipex(t_node *node)
{
	size_t	cnt_node;
	t_node	*head;
	size_t	i;

	head = node;
	cnt_node = get_node_cnt(node);
	i = 0;
	if (cnt_node <= 1)
		exec_cmd(node);
	else
	{
		while (i < cnt_node)
		{
			if (i < cnt_node - 1)
				pipe(node->pfd);
			node->pid = fork();
			if (node->pid == 0)
			{
				if (i != 0)
					input_pipe_dup_close(head->pfd);
				else
					output_pipe_dup_close(node->pfd);
				exec_cmd(node);
			}
			else
			{
				// if (i != 0)
				// 	close_pipe(node, head);
			}
			node = node->next;
			i++;
		}
		wait(NULL);
		exit(1);
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

void	output_pipe_dup_close(int fd[2])
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	input_pipe_dup_close(int fd[2])
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	close_pipe(t_node *node, t_node *cur)
{
	while (cur->next != node && cur->next != NULL)
	{
		puts("b");
		cur = cur->next;
	}
	close(cur->pfd[0]);
	close(cur->pfd[1]);
}
