/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:48:29 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/27 21:05:14 by susasaki         ###   ########.fr       */
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
		fatal_error ("malloc");
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}
