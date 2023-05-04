/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:50 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/04 17:52:40 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//単体のとき
static void	bi_only_export_env(t_environ *env)
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
		if (ft_strcmp(environ->name, var->name) == 0)
		{
			if (environ->value != NULL)
				free(environ->value);
			if (value == NULL)
				environ->value = NULL;
			else
			{
				environ->value = ft_strdup(value);
				if (environ->value == NULL)
					perror("strdup");
			}
			break ;
		}
		environ = environ->next;
	}
}

int	bi_export(t_environ *environ, char **argv, int argc)
{
	char		*name;
	char		*value;
	t_environ	*var;

	if (argc == 1)
		bi_only_export_env(environ);
	else if (argc == 2)
	{
		name = make_name(argv[1]);
		if (name == NULL)
		{
			put_error_msg_endl("export: not a valid identifier");
			g_global.status = 1;
			return (-1);
		}
		var = find_variable(environ, name);
		value = make_value(argv[1]);
		if (value == NULL)
		{
			value = malloc(1);
			value[0] = '\0';
		}
		if (var != NULL)
			override_val(environ, var, value);
		else
			environ_nodeadd_back(environ, environ_node_new(ft_strdup(name),
						ft_strdup(value)));
		free(name);
		free(value);
	}
	g_global.status = 0;
	return (0);
}
