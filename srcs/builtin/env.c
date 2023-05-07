/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:27:04 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/07 14:20:11 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bi_env(int argc, t_environ *environ)
{
	t_environ	*tmp;

	g_global.status = 0;
	tmp = environ;
	if (argc > 1)
	{
		put_error_msg_endl("env: too many arguments");
		g_global.status = 127;
		return (-1);
	}
	// printf("\x1b[31m");
	// printf("test1\n");
	// printf("environ->name = %s\n",environ->name);
	// // printf("environ->value = %s\x1b[0m\n",environ->value);
	// printf("\x1b[0m");
	while (tmp != NULL)
	{
		printf("%s", tmp->name);
		if (tmp->value != NULL)
			printf("=%s", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
	return (0);
}
