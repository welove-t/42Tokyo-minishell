/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:50 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/04 13:51:22 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*make_name(char *str)
{
	char	*name;
	int		fir_len;

	if (!(('a' <= *str && *str <= 'z') || ('A' <= *str && *str <= 'Z')
			|| *str == '_'))
		return (NULL);
	fir_len = first_strlen(str);
	if (fir_len == -1)
		return (NULL);
	name = (char *)malloc(fir_len + 1);
	if (!name)
		fatal_error("malloc");
	ft_strlcpy(name, str, fir_len + 1);
	// strncpy(name, str, fir_len);
	//TODO: ft_strlcpyで終端文字までコピーしているので、下記のコードは不必要かも
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
	if (!value)
		fatal_error("malloc");
	ft_strlcpy(value, str + fir_len + 1, lat_len + 1);
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
	// printf("value = %s\n",value);
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
			environ_nodeadd_back(environ, environ_node_new(ft_strdup(name), ft_strdup(value)));
		free(name);
		free(value);
	}
	g_global.status = 0;
	return (0);
}
