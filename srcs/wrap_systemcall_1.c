/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_systemcall_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:30:00 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/30 19:48:05 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_close(int fd)
{
	if (close(fd) < 0)
	{
		fatal_error("close");
		exit(1);
	}
}

void	do_write(int fd, const void *buf, size_t count)
{
	if (write(fd, buf, count) < 0)
	{
		fatal_error("write");
		exit(1);
	}
}

void	do_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
	{
		fatal_error("dup2");
		exit(1);
	}
}

void	do_pipe(int pipefd[2])
{
	if (pipe(pipefd) < 0)
	{
		fatal_error("pipe");
		exit(1);
	}
}
