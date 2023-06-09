/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:58:24 by terabu            #+#    #+#             */
/*   Updated: 2023/05/04 13:58:19 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
