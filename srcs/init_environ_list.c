/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environ_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:56:04 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/23 18:48:29 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

int	first_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	latter_strlen(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (-1);
	i++;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
	{
		i++;
		res++;
	}
	return (res);
}

t_environ	*init_environ_list()
{
	int			i;
	int			j;
	int			n;
	char		*name;
	char		*value;
	char		**tmp;
	t_environ	*env_list;
	t_envinfo	*env_info;
	int			flag;
	t_environ	*new;

	i = 0;
	flag = 0;
	//環境変数environの値を直接変更したくないため
	tmp = environ;
	env_list = NULL;
	env_info = (t_envinfo *)malloc(sizeof(t_envinfo));
	env_info->head = NULL;
	//環境変数を1行ずつ出力
	while (tmp[i] != NULL)
	{
		j = 0;
		n = 0;
		name = make_name(tmp[i]);
		value = make_value(tmp[i]);
		new = environ_node_new(name, value);
		new->name = name;
		new->value = value;
		if (flag == 0)
		{
			env_list = new;
			env_info->head = env_list;
			flag = 1;
		}
		else
		{
			env_list->next = new;
			env_list = env_list->next;
		}
		i++;
	}
	env_list = NULL;
	env_list = env_info->head;
	return (env_list);
}
