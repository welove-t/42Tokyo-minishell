/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:58:24 by terabu            #+#    #+#             */
/*   Updated: 2023/04/23 12:47:36 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tokenize_error(const char *location, char **rest, char *line, int flg)
{
	syntax_error = true;
	perror_prefix();
	if (flg < 0)
		dprintf(STDERR_FILENO, "syntax error: %s\n", location);
	else
	{
		dprintf(STDERR_FILENO, "syntax error near unexpected character \
		`%c' in %s\n", *line, location);
	}
	while (*line)
		line++;
	*rest = line;
}
