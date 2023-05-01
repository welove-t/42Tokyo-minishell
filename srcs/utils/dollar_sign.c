/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:40:25 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/01 15:55:26 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	last_exit_status(char **new_word)
{
	char	*str;
	char *begin;

	str = ft_itoa(g_global.status);
	begin = str;
	while (*begin != '\0')
		append_char(new_word, *begin++);
	free(str);
}



static void	expand_env(char **new_word, char *p)
{
	char	*value;

	if (*p == '?')
	{
		last_exit_status(new_word);
		return ;
	}
	//TODO:リストから取得するようにする
	value = getenv(p);
	if (value == NULL)
	{
		append_char(new_word, '\0');
		return ;
	}
	while (*value != '\0')
		append_char(new_word, *value++);
	return ;
}

int	handle_dollar_sign(char **p, char **exp_tmp)
{
	(*p)++;
	if (**p == ' ' || **p == '\t' || **p == '\0')
		return (1);
	else
	{
		if (**p == '?')
			append_char(exp_tmp, *((*p)++));
		else
		{
			while (**p && !is_metacharacter(**p) && **p != '\"' && **p != '\'')
				append_char(exp_tmp, *((*p)++));
		}
	}
	return (0);
}

void	dollar_sign(char **p, char **new_word)
{
	char	*exp_tmp;

	exp_tmp = NULL;
	while (**p && !is_metacharacter(**p) && **p != '\"' && **p != '\'')
	{
		if (**p == DOLLAR_SIGN)
		{
			if (handle_dollar_sign(p, &exp_tmp) == 1)
				append_char(new_word, '$');
			if (exp_tmp)
			{
				expand_env(new_word, exp_tmp);
				free(exp_tmp);
				exp_tmp = NULL;
			}
		}
		else
			break ;
	}
}
