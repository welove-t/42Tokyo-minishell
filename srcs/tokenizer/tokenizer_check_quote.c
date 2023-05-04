/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_check_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:01:56 by terabu            #+#    #+#             */
/*   Updated: 2023/04/20 16:47:56 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quote(char **line)
{
	while (**line && !is_metacharacter(**line))
	{
		if (**line == SINGLE_QUOTE_CHAR)
		{
			if (!consume_single_quote(line))
				return (-1);
		}
		else if (**line == DOUBLE_QUOTE_CHAR)
		{
			if (!consume_double_quote(line))
				return (-2);
		}
		else
			(*line)++;
	}
	return (0);
}

bool	consume_single_quote(char **line)
{
	(*line)++;
	while (**line && **line != SINGLE_QUOTE_CHAR)
		(*line)++;
	if (**line == '\0')
		return (false);
	else
		(*line)++;
	return (true);
}

bool	consume_double_quote(char **line)
{
	(*line)++;
	while (**line && **line != DOUBLE_QUOTE_CHAR)
		(*line)++;
	if (**line == '\0')
		return (false);
	else
		(*line)++;
	return (true);
}
