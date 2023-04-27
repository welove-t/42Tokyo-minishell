/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:56:13 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/27 12:07:10 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_param_name(char *str)
{
	if (ft_strchr(str, '=') != NULL)
	{
		put_error_msg_endl("unset: invalid parameter name");
		return (0);
	}
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

void	remove_variable(t_environ *environ, t_environ *var)
{
	while (environ != NULL)
	{
		if (environ->next->name == var->name)
		{
			environ->next = environ->next->next;
			break ;
		}
		environ = environ->next;
	}
}

int	bi_unset(t_environ *environ, char **argv, int argc)
{
	t_environ	*var;

	if (argc < 2)
	{
		return (-1);
	}
	if (!is_valid_param_name(argv[1]))
	{
		return (-1);
	}
	var = find_variable(environ, argv[1]);
	if (var == NULL)
	{
		return (-1);
	}
	remove_variable(environ, var);
	return (0);
}
