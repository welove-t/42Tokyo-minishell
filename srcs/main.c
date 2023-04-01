/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:34:05 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/01 10:26:43 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// グローバル変数
// test
char **g_environ;

int main(void)
{
	char *input;

	//pidを宣言
	pid_t	pid;
	//入力を受け続ける
	while(1)
	{
		//プロンプトの入力待ち
		input = readline(">");
		//ctrl-Dが押されたら、EOFが代入され、whileから抜ける。
		if (input == NULL)
		{
			printf("\nProgram exited\n");
			break;
		}
		//入力内容を履歴に追加する。
		if (input != NULL)
			add_history(input);

		//NULLの場合、何もしない
		if (input == NULL)
		{
			printf("\n");
		}
		//文字列が入力された場合、パスと一致するかどうか
		else
		{
			/*
			子プロセスを生成。複数のcmdを同時に実行したいから
			fork()を使う。
			*/
			//子プロセスを生成(親と全く同じ動作)
			pid = fork();
			/*
			[Child]が指している親プロセスのIDと[Parent]のIDが正しければ、
			正常にプログラムが実行できている。
			*/
			//子プロセスの場合
			if (pid == 0)
			{
				printf("\x1b[32m[Child Process]\x1b[0m\n");
				//子プロセスの親プロセスPID
				printf("Parent PPID = %d,",getppid());
				//自身のPIDを出力
				printf("Child PID = %d\n",getpid());

				line_matches_cmd(input);
				//子プロセスの処理終了
				exit(0);
			}
			else if(pid > 0)
			{
				printf("\x1b[32m[Parent Process]\x1b[0m\n");
				// 親プロセスのPIDを出力
				printf("Parent PPID = %d\n",getpid());
				printf("Wait for Child Process to finish\n");
				// 子プロセスの処理終了を待つ
				wait(NULL);
				printf("Child process finished\n");
			}
			else
			{
				printf("\x1b[31mError fork()\x1b[0m\n");
			}
			// str_matches_cmd(input);
		}
		//readline関数で割り当てたメモリを解放する。
		free(input);
	}
	return 0;
}
