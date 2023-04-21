/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:30:37 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/21 20:48:16 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


//ctrl-\が押された時に呼ばれるシグナルハンドラ
static void signal_backslash()
{
   return ;
}

static void signal_c_cmd()
{
	// printf("signal_c_cmd()が呼ばれた\n");
	rl_on_new_line(); // 新しい行に移動する
	rl_replace_line("", 0);
	printf("\n"); // 改行を出力して新しい行を開始
	rl_redisplay(); // 新しい行を再表示する
}

void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		// signal_setget_status(SIG_SET, sig);
		signal_c_cmd();
	}
	else if (sig == SIGQUIT)
	{
		// signal_setget_status(SIG_SET, sig);
		signal_backslash();
	}
	return ;
}

void signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		/*
		rl_doneが0でなければ、readlineは終了せず、
		プロンプトを維持し続けます。
		一方、rl_doneが0の場合、readlineは終了し、
		プログラムはreadlineから戻ります。
		通常は、rl_doneはreadlineの初期化時にゼロに設定され、
		プログラムが終了するときに1に設定されます。*/
		g_status = 1;
		// Ctrl-Cで入力された文字列を削除する
        rl_replace_line("", 0);
		rl_on_new_line();
        rl_redisplay();
	}
	return ;
}

