/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:58:24 by terabu            #+#    #+#             */
/*   Updated: 2023/05/04 11:31:39 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_error(t_token **rest, t_token *tok)
{
	g_global.syntax_error = true;
	perror_prefix();
	put_error_msg_endl("syntax error !!");
	g_global.status = 258;
	while (tok && tok->kind != TK_EOF)
		tok = tok->next;
	*rest = tok;
}

void	xperror(const char *location)
{
	perror_prefix();
	perror(location);
}
