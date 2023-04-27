/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:58:24 by terabu            #+#    #+#             */
/*   Updated: 2023/04/27 18:20:18 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tokenize_error(char *location, char **rest, char *line, int flg)
{
	g_global.syntax_error = true;
	perror_prefix();
	if (flg < 0)
	{
		put_error_msg("syntax error: ");
		put_error_msg_endl(location);
	}
	else
	{
		put_error_msg("syntax error near unexpected character `");
		put_error_char(*line);
		put_error_msg("' in ");
		put_error_msg_endl(location);
	}
	while (*line)
		line++;
	*rest = line;
}
