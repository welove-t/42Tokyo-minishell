/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:34:05 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/16 19:46:19 by susasaki         ###   ########.fr       */
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

	// 初期設定
	syntax_error = false;
	//入力を受け続ける
	while(1)
	{
		//プロンプトの入力待ち
		input = readline(">");
		//ctrl-Dが押されたら、EOFが代入され、whileから抜ける。
		if (input == NULL)
		{
			// printf("\nProgram exited\n");
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
				line_matches_cmd(input);
				//子プロセスの処理終了
				exit(0);
			}
			else if(pid > 0)
			{
				// 親プロセスのPIDを出力
				// 子プロセスの処理終了を待つ
				wait(&g_status);
				g_status = WEXITSTATUS(g_status);
			}
			else
			{
				printf("\x1b[31mError fork()\x1b[0m\n");
			}
		}
		//readline関数で割り当てたメモリを解放する。
		free(input);
	}
	return 0;
}
