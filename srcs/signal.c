/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:30:37 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/20 16:32:46 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


//ctrl-\が押された時に呼ばれるシグナルハンドラ
static void signal_backslash()
{
   return ;
}

int signal_setget_status(int style, int sig)
{
	// printf("~~ signal_setget_status ~~\n");
	static int sig_status;
	// printf("sig = %d\n",sig);
	// printf("style = %d\n",style);
	if (style == SIG_GET)
	{
		// printf("SIG_GET\n");
		return (sig_status);
	}
	else if(style == SIG_SET)
	{
		//sig_statusにセットする
		// printf("SIG_SET\n");
		sig_status = sig;
	}
	// printf("sig_status = %d\n",sig_status);
	return (0);
}

static void signal_c_cmd()
{
	printf("\n"); // 改行を出力して新しい行を開始
	rl_replace_line("", 0);
	rl_on_new_line(); // 新しい行に移動する
	rl_redisplay(); // 新しい行を再表示する
}

void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		signal_setget_status(SIG_SET, sig);
		signal_c_cmd();
	}
	else if (sig == SIGQUIT)
	{
		signal_setget_status(SIG_SET, sig);
		signal_backslash();
	}
	return ;
}

void signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		rl_done = 0;
	}
	// else if (sig == SIGQUIT)
	// {
	// 	signal_setget_status(SIG_SET, sig);
	// 	signal_backslash();
	// }
	return ;
}

