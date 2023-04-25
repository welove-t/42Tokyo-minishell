/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:27:04 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/25 19:20:09 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	bi_env(int argc, t_environ *environ)
{
	t_environ	*tmp;

	tmp = environ;
	if (argc > 1)
	{
		printf("env too many arguments\n");
		return ;
	}
	// 環境変数を1行ずつ出力
	while (tmp != NULL)
	{
		printf("%s", tmp->name);
		if (tmp->value != NULL)
			printf("=%s", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}

// int main(void)
// {
//     bl_env();
//     return (0);
// }