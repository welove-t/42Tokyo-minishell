/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:40:25 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/23 19:03:36 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	last_exit_status(char **new_word)
{
	char	*str;

	str = ft_itoa(g_status);
	while (*str != '\0')
		append_char(new_word, *str++);
}

static void	expand_env(char **new_word, char *p)
{
	char	*value;
	char	*new;

	if (*p == '?')
	{
		last_exit_status(new_word);
		return ;
	}
	value = getenv(p);
	if (value == NULL)
	{
		new = malloc(1);
		new[0] = '\0';
		*new_word = new;
		// append_char(new_word, '\0');
		// printf("\n"); // 改行を出力して新しい行を開始
		// free(new);
		return ;
	}
	while (*value != '\0')
		append_char(new_word, *value++);
	return ;
}

int	handle_dollar_sign(char **p, char **exp_tmp)
{
	if (*((*p) + 1) == ' ' || *((*p) + 1) == '\t' || *((*p) + 1) == '\0')
		return (1);
	else
	{
		(*p)++;
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
				break ;
			if (exp_tmp)
			{
				expand_env(new_word, exp_tmp);
				free(exp_tmp);
				exp_tmp = NULL;
			}
			else
			{
				append_char(new_word, *((*p)++));
				append_char(new_word, *((*p)++));
				break ;
			}
		}
		else
			break ;
	}
}
