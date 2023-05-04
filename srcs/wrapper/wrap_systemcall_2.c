/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_systemcall_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:41:28 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/04 15:06:04 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_unlink(char *str)
{
	if (unlink(str) < 0)
		fatal_error("unlink");
}

void	do_pipe(int pipefd[2])
{
	if (pipe(pipefd) < 0)
		fatal_error("pipe");
}
