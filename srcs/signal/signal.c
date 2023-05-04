/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:30:37 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/04 17:52:11 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_backslash(void)
{
	return ;
}

void	signal_c_cmd(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
	g_global.status = 1;
}

int	signal_monitor(void)
{
	if (g_global.status == 1)
		rl_done = 1;
	return (0);
}
