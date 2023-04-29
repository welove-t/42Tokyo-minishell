/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:37:22 by terabu            #+#    #+#             */
/*   Updated: 2023/04/29 13:55:55 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_open_redir_out(char *filepath)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		error_file(filepath);
	return (fd);
}

int	do_open_redir_in(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		error_file(filepath);
	return (fd);
}

int	do_open_redir_append(char *filepath)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		error_file(filepath);
	return (fd);
}
