/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:34:05 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/19 16:17:02 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ctrl-cが押された時に呼ばれるシグナルハンドラ
void signal_c()
{
    printf("\n"); // 改行を出力して新しい行を開始
	// プロンプトとして表示されている現在の行を消去
    rl_replace_line("", 0);
    rl_on_new_line(); // 新しい行に移動する
    rl_redisplay(); // 新しい行を再表示する
}

//ctrl-\が押された時に呼ばれるシグナルハンドラ
void signal_backslash()
{
   return ;
}

void signal_handler(int sig)
{
	if (sig == SIGINT)
		signal_c();
	else if (sig == SIGQUIT)
		signal_backslash();
	return ;
}

int main(void)
{
	char *input;
	int	wstatus;

	pid_t	pid;

	syntax_error = false;

	signal(SIGINT,signal_handler);
    signal(SIGQUIT,signal_handler);
	//入力を受け続ける
	while(1)
	{
		//プロンプトの入力待ち
		input = readline("minishell> ");
		//ctrl-Dが押されたら、EOFが代入され、whileから抜ける。
		if (input == NULL)
			break;
		//入力内容を履歴に追加する。
		if (input != NULL)
			add_history(input);
		if (input == NULL)
			printf("\n");
		else
		{
			//子プロセスを生成
			pid = fork();
			//子プロセスの場合
			if (pid == 0)
			{
				line_matches_cmd(input);
				//子プロセスの処理終了
				exit(0);
			}
			else if(pid > 0)
			{
				wait(&wstatus);
				/*
				子プロセスが正常に終了した場合に真を返す。
				*/
				// printf("status: %08x\n", wstatus);
				if (WIFEXITED(wstatus))
				{
					g_status = WEXITSTATUS(wstatus);
					// printf("status parse: %d\n", g_status);
				}
				/*
				シグナルで終了した時
				*/
				// else if (WIFSIGNALED(wstatus))
				else
				{
					g_status = WTERMSIG(wstatus);
					// printf("status parse: %d\n", g_status);
				}
			}
			else
				printf("\x1b[31mError fork()\x1b[0m\n");
		}
		free(input);
	}
	return 0;
}
