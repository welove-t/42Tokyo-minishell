/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:56:13 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/06 02:38:12 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_param_name(char *str)
{
	if (ft_strchr(str, '=') != NULL)
		return (0);
	return (1);
}

t_environ	*find_variable(t_environ *environ, char *str)
{
	t_environ	*tmp;

	tmp = environ;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, str) == 0)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

/*
void	remove_variable(t_environ *environ, t_environ *var)
{
	t_environ	*tmp;

	while (environ != NULL)
	{
		//TODO:先頭の要素を削除した時にセグフォ。unsetで削除できない
		if (environ->next->name == var->name)
		{
			tmp = environ->next;
			environ->next = environ->next->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			break ;
		}
		environ = environ->next;
	}
}
*/

void	remove_variable(t_environ **environ, t_environ *var)
{
	t_environ	*tmp;
	t_environ	*fast;

	fast = *environ;
	//TODO: 先頭ノードを消しきれていない。
	// 先頭ノードの場合
	if ((*environ)->name == var->name)
	{
		tmp = *environ;
		*environ = (*environ)->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		return;
	}

	// 2番目以降のノードを削除する場合
	while ((*environ)->next != NULL)
	{
		if ((*environ)->next->name == var->name)
		{
			tmp = (*environ)->next;
			(*environ)->next = (*environ)->next->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			break;
		}
		*environ = (*environ)->next;
	}
	*environ = fast;
}

int	bi_unset(t_environ *environ, char **argv, int argc)
{
	t_environ	*var;

	g_global.status = 0;
	if (argc < 2)
	{
		return (-1);
	}
	if (argc > 2)
	{
		put_error_msg_endl("unset: too many arguments");
		g_global.status = 1;
		return (-1);
	}
	if (!is_valid_param_name(argv[1]))
	{
		put_error_msg_endl("unset: invalid parameter name");
		return (-1);
	}
	var = find_variable(environ, argv[1]);
	if (var == NULL)
	{
		put_error_msg_endl("unset: can't find variable");
		return (-1);
	}
	remove_variable(&environ, var);
	printf("environ->name = %s\n",environ->name);
	return (0);
}
