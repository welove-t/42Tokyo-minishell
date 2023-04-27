/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:58:24 by terabu            #+#    #+#             */
/*   Updated: 2023/04/27 18:19:57 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_error(char *location, t_token **rest, t_token *tok)
{
	g_global.syntax_error = true;
	perror_prefix();
	put_error_msg("syntax error near unexpected token `");
	put_error_msg(tok->word);
	put_error_msg("' in ");
	put_error_msg_endl(location);
	while (tok && tok->kind != TK_EOF)
		tok = tok->next;
	*rest = tok;
}

void	xperror(const char *location)
{
	perror_prefix();
	perror(location);
}
