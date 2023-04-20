/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:45:00 by terabu            #+#    #+#             */
/*   Updated: 2023/04/20 11:24:57 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	output_pipe_dup_close(int fd[2]);
void	input_pipe_dup_close(int fd[2]);
void	close_pipe(t_node *node, size_t i);

void	pipex(t_node *node, size_t cnt_node)
{
	size_t	i;

	i = 0;
	while (i < cnt_node)
	{
		if (i < cnt_node - 1)
			pipe(node->pfd);
		node->pid = fork();
		if (node->pid == 0)
		{
			if (i != 0)
				input_pipe_dup_close(node->prev->pfd);
			if (i != cnt_node - 1)
				output_pipe_dup_close(node->pfd);
			exec_cmd(node);
		}
		else
			close_pipe(node, i);
		node = node->next;
		i++;
	}
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

void	close_pipe(t_node *node, size_t i)
{
	if (i < 1)
		return ;
	close(node->prev->pfd[0]);
	close(node->prev->pfd[1]);
}

void	waitpid_pipex(t_node *node)
{
	int			status;

	while (node != NULL)
	{
		if (waitpid(node->pid, &status, 0) < 0)
			perror("waitpid");
		node = node->next;
	}
}
