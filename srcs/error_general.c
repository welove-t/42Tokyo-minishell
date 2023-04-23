/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:58:24 by terabu            #+#    #+#             */
/*   Updated: 2023/04/23 20:32:53 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	perror_prefix(void)
{
	put_error_msg(ERROR_PREFIX);
}

void	fatal_error(char *msg)
{
	perror_prefix();
	put_error_msg("Fatal Error: ");
	put_error_msg_endl(msg);
	exit(1);
}

void	assert_error(char *msg)
{
	perror_prefix();
	put_error_msg("Fatal Error: ");
	put_error_msg_endl(msg);
	exit(255);
}

void	err_exit(char *location, char *msg, int status)
{
	perror_prefix();
	put_error_msg(location);
	put_error_msg(": ");
	put_error_msg_endl(msg);
	exit(status);
}

void	todo(char *msg)
{
	perror_prefix();
	put_error_msg("TODO: ");
	put_error_msg_endl(msg);
	exit(255);
}
