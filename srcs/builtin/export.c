/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:50 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/27 11:43:08 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*make_name(char *str)
{
	char	*name;
	int		fir_len;

	fir_len = first_strlen(str);
	if (fir_len == -1)
		return (NULL);
	name = (char *)malloc(fir_len + 1);
	strncpy(name, str, fir_len);
	name[fir_len] = '\0';
	return (name);
}

char	*make_value(char *str)
{
	char	*value;
	int		lat_len;
	int		fir_len;

	fir_len = first_strlen(str);
	lat_len = latter_strlen(str);
	if (lat_len == -1)
		return (NULL);
	value = (char *)malloc(lat_len + 1);
	strncpy(value, str + fir_len + 1, lat_len);
	value[lat_len] = '\0';
	return (value);
}

//単体のとき
void	bi_only_export_env(t_environ *env)
{
	t_environ	*print_env;

	print_env = env;
	while (print_env != NULL)
	{
		printf("declare -x %s", print_env->name);
		if (print_env->value != NULL)
			printf("=\"%s\"", print_env->value);
		printf("\n");
		print_env = print_env->next;
	}
}

static void	override_val(t_environ *environ, t_environ *var, char *value)
{
	while (environ != NULL)
	{
		if (environ->name == var->name)
		{
			environ->value = value;
			break ;
		}
		environ = environ->next;
	}
}

int	bi_export(t_environ *environ, char **argv, int argc)
{
	char		*name;
	char		*value;
	t_environ	*new;
	t_environ	*var;

	if (argc == 1)
		bi_only_export_env(environ);
	else if (argc == 2)
	{
		name = make_name(argv[1]);
		if (name == NULL)
		{
			put_error_msg_endl("export: not a valid identifier");
			return (-1);
		}
		var = find_variable(environ, name);
		value = make_value(argv[1]);
		if (var != NULL)
			override_val(environ, var, value);
		else
		{
			new = environ_node_new(name, value);
			environ_nodeadd_back(environ, new);
		}
	}
	return (0);
}

