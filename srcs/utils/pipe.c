/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:45:00 by terabu            #+#    #+#             */
/*   Updated: 2023/04/27 14:04:12 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	output_pipe_dup_close(int fd[2]);
void	input_pipe_dup_close(int fd[2]);
void	close_pipe(t_node *node, size_t i);

void	pipex(t_node *node, size_t cnt_node, t_environ *environ)
{
	size_t	i;
	int		flag;

	i = 0;
	while (i < cnt_node)
	{
		if (i < cnt_node - 1)
			pipe(node->pfd);
		signal(SIGINT, SIG_IGN);
		node->pid = fork();
		if (node->pid == 0)
		{
			if (i != 0)
				input_pipe_dup_close(node->prev->pfd);
			if (i != cnt_node - 1)
				output_pipe_dup_close(node->pfd);
			flag = search_bi_cmd(node, environ);
			// ビルトインコマンドが失敗した時。
			if (flag == -1)
				exit(EXIT_FAILURE);
			else if (flag == 0)
				exit(EXIT_SUCCESS);
			else
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
	int	status;

	while (node != NULL)
	{
		if (waitpid(node->pid, &status, 0) < 0)
			perror("waitpid");
		node = node->next;
	}
}
