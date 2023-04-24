/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bi_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:45:48 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/24 18:43:54 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int search_bi_cmd_helper(t_node *node)
{
	if (strcmp(node->args->word,"pwd") == 0)
	{
		bi_pwd();
		return (1);
	}
	return (0);
}

int search_bi_cmd(t_node *node)
{
	int res;
	res = search_bi_cmd_helper(node);
	// printf("res = %d\n",res);
	return (res);
}