/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:30:37 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/04 14:26:24 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_backslash(void)
{
	return ;
}

void	signal_c_cmd(void)
{
	rl_on_new_line(); // 新しい行に移動する
	rl_replace_line("", 0);
	printf("\n");   // 改行を出力して新しい行を開始
	rl_redisplay(); // 新しい行を再表示する
	g_global.status = 1;
}

int	signal_monitor(void)
{
	if (g_global.status == 1)
		rl_done = 1;
	//0だと終了
	return (0);
}
