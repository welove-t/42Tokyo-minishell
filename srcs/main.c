/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:34:05 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/21 20:54:54 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	char *input;
	// int wstatus;

	// pid_t pid;

	syntax_error = false;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	// 入力を受け続ける
	while (1)
	{
		// printf("回った\n");
		// write(1, "round\n", strlen("round\n"));
		// プロンプトの入力待
		input = readline("minishell> ");
		// ctrl-Dが押されたら、EOFが代入され、whileから抜ける。
		if (input == NULL)
			break;
		// 入力内容を履歴に追加する。
		if (input != NULL)
			add_history(input);
		if (input == NULL)
			printf("\n");
		else
		{
			// 子プロセスを生成
			//  pid = fork();
			// 子プロセスの場合
			//  if (pid == 0)
			//  {
			// 子プロセスの方ではmainの方のシグナルハンドラを呼ばないようにする。
			/*TODO: heredocumentの時に出力が少しおかしいが、もしかしたらfork()が関係しているかも知れないので、
			fork()の所を改善してから修正すること。*/
			signal(SIGINT, SIG_DFL);
			// signal(SIGQUIT,SIG_DFL);
			line_matches_cmd(input);
			// 子プロセスの処理終了
			// 		exit(0);
			// 	}
			// 	else if(pid > 0)
			// 	{
			// 		wait(&wstatus);
			// 		signal(SIGINT, signal_handler);
			// 		/*
			// 		子プロセスが正常に終了した場合に真を返す。
			// 		*/
			// 		// printf("status: %08x\n", wstatus);
			// 		if (WIFEXITED(wstatus))
			// 		{
			// 			g_status = WEXITSTATUS(wstatus);
			// 			// printf("status parse: %d\n", g_status);
			// 		}
			// 		/*
			// 		シグナルで終了した時
			// 		*/
			// 		// else if (WIFSIGNALED(wstatus))
			// 		else
			// 		{
			// 			g_status = WTERMSIG(wstatus);
			// 			// printf("status parse: %d\n", g_status);
			// 		}
			// 	}
			// 	else
			// 		printf("\x1b[31mError fork()\x1b[0m\n");
		}
		free(input);
	}
	return 0;
}
