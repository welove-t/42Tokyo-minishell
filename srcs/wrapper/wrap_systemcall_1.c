/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_systemcall_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:30:00 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/04 15:04:42 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	do_dup(int oldfd)
{
	int	fd;

	fd = dup(oldfd);
	if (fd < 0)
	{
		fatal_error("dup");
		exit(1);
	}
	return (fd);
}

void	do_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
	{
		fatal_error("dup2");
		exit(1);
	}
}
