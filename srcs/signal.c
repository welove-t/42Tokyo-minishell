/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:30:37 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/22 19:43:57 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_backslash(void)
{
	return ;
}

void	signal_c_cmd(void)
{
	// printf("signal_c_cmd()が呼ばれた\n");
	rl_on_new_line(); // 新しい行に移動する
	rl_replace_line("", 0);
	printf("\n");   // 改行を出力して新しい行を開始
	rl_redisplay(); // 新しい行を再表示する
}

void	signal_handler(int sig)
{
	printf("signal_handlerが呼ばれた(%d)", sig);
	if (sig == SIGINT)
		signal_c_cmd();
	else if (sig == SIGQUIT)
		signal_backslash();
	return ;
}

void	signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		// printf("\nsignal_handler_heredoc()が呼ばれた\n");
		// Ctrl-Cで入力された文字列を削除する
		// rl_on_new_line(); // 新しい行に移動する
		// rl_replace_line("", 0);
		// printf("\n"); // 改行を出力して新しい行を開始
		// rl_redisplay(); // 新しい行を再表示する
	}
	return ;
}
