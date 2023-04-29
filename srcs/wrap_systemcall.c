/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_systemcall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:30:00 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/29 13:51:47 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    do_close(int fd)
{
    if (close(fd) < 0)
    {
        fatal_error("close");
        exit(1);
    }
}

void    do_open(const char *pathname, int flags)
{
    if (open(pathname, flags) < 0)
    {
        fatal_error("open");
        exit(1);
    }
}

void    do_write(int fd, const void *buf,size_t count)
{
    if (write(fd, buf, count) < 0)
    {
        fatal_error("write");
        exit(1);
    }
}