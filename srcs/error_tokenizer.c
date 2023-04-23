/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:58:24 by terabu            #+#    #+#             */
/*   Updated: 2023/04/23 16:39:20 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tokenize_error(char *location, char **rest, char *line, int flg)
{
	syntax_error = true;
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
