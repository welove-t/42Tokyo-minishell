/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:48:29 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/05 16:24:11 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//最後尾にノードを追加する。
void	environ_nodeadd_back(t_environ *env, t_environ *new)
{
	if (env == NULL)
		return ;
	while (env->next != NULL)
		env = env->next;
	env->next = new;
	env = env->next;
}

//新たにノードを作る
t_environ	*environ_node_new(char *name, char *value)
{
	t_environ	*new;

	new = (t_environ *)malloc(sizeof(t_environ));
	if (!new)
		fatal_error("malloc");
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

char	*make_name(char *str)
{
	char	*name;
	int		fir_len;

	//TODO: 2文字目以降はアルファベット+数字+_
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
