/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:23:04 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/30 18:23:50 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipex_utils(t_node *node, int flag)
{
	if (flag == -1)
		exit(EXIT_FAILURE);
	else if (flag == 0)
		exit(EXIT_SUCCESS);
	else
		exec_cmd(node);
}
