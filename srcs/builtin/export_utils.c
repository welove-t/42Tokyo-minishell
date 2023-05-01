/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:48:29 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/01 14:30:37 by susasaki         ###   ########.fr       */
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

// void	updata_environ(t_environ *env)
// {
// 	int			count;
// 	char		**new_environ;
// 	t_environ	*ptr;
// 	int			i;

// 	i = 0;
// 	count = 0;
// 	ptr = env;
// 	while (ptr != NULL)
// 	{
// 		count++;
// 		ptr = ptr->next;
// 	}
// 	new_environ = (char **)malloc((count + 1) * sizeof(char *));
// 	if (!new_environ)
// 		fatal_error("malloc");
// 	new_environ[count] = NULL;
// 	ptr = env;
// 	while (i < count)
// 	{
// 		new_environ[i] = ft_strdup(ptr->name);
// 		if (ptr->value != NULL)
// 		{
// 			new_environ[i] = ft_strjoin(new_environ[i], "=");
// 			new_environ[i] = ft_strjoin(new_environ[i], ptr->value);
// 		}
// 		ptr = ptr->next;
// 	}
// 	env = *new_environ;
// }
