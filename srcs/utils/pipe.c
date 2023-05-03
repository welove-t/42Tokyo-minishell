/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:45:00 by terabu            #+#    #+#             */
/*   Updated: 2023/05/03 08:33:07 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		output_pipe_dup_close(int fd[2]);
void		input_pipe_dup_close(int fd[2]);
void		close_pipe(t_node *node, size_t i);

void	pipex(t_node *node, size_t cnt_node, t_environ *environ)
{
	size_t	i;
	int		flag;

	i = 0;
	while (i < cnt_node)
	{
		if (i < cnt_node - 1)
			do_pipe(node->pfd);
		signal(SIGINT, SIG_IGN);
		node->pid = fork();
		if (node->pid == 0)
		{
			if (i != 0)
				input_pipe_dup_close(node->prev->pfd);
			if (i != cnt_node - 1)
				output_pipe_dup_close(node->pfd);
			flag = search_bi_cmd(node, environ);
			pipex_utils(node, flag, environ);
		}
		else
			close_pipe(node, i);
		node = node->next;
		i++;
	}
}

void	output_pipe_dup_close(int fd[2])
{
	do_close(fd[0]);
	do_dup2(fd[1], STDOUT_FILENO);
	do_close(fd[1]);
}

void	input_pipe_dup_close(int fd[2])
{
	do_close(fd[1]);
	do_dup2(fd[0], STDIN_FILENO);
	do_close(fd[0]);
}

void	close_pipe(t_node *node, size_t i)
{
	if (i < 1)
		return ;
	do_close(node->prev->pfd[0]);
	do_close(node->prev->pfd[1]);
}

void	waitpid_pipex(t_node *node, int *wstatus)
{
	while (node != NULL)
	{
		if (waitpid(node->pid, wstatus, 0) < 0)
			fatal_error("waitpid");
		node = node->next;
	}
}
