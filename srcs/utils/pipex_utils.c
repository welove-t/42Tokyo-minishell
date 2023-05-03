/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:23:04 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/03 08:33:30 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipex_utils(t_node *node, int flag, t_environ *environ)
{
	if (flag == -1)
		exit(EXIT_FAILURE);
	else if (flag == 0)
		exit(EXIT_SUCCESS);
	else
		exec_cmd(node, environ);
}
