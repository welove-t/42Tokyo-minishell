/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_check_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:01:56 by terabu            #+#    #+#             */
/*   Updated: 2023/05/04 17:39:40 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static bool	consume_single_quote(char **line)
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

static bool	consume_double_quote(char **line)
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

