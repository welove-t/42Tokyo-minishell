/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:58:24 by terabu            #+#    #+#             */
/*   Updated: 2023/04/21 11:11:19 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define ERROR_PREFIX "minishell: "

void	tokenize_error(const char *location, char **rest, char *line)
{
	syntax_error = true;
	perror_prefix();
	dprintf(STDERR_FILENO, "syntax error near unexpected character \
	`%c' in %s\n", *line, location);
	// exit(1);
	while (*line)
		line++;
	*rest = line;
}

void	parse_error(const char *location, t_token **rest, t_token *tok)
{
	syntax_error = true;
	perror_prefix();
	dprintf(STDERR_FILENO, "syntax error near unexpected token \
	`%s' in %s\n", tok->word, location);
	while (tok && tok->kind != TK_EOF)
		tok = tok->next;
	*rest = tok;
}

void	xperror(const char *location)
{
	perror_prefix();
	perror(location);
}
