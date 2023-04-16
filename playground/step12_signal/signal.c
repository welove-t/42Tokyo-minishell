/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:21:01 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/15 18:54:27 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>

//ctrl-cが押された時に呼ばれるシグナルハンドラ
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
    /*
    シグナルハンドラを設定する
    SIGINT = ctrl-cが押された時にシグナルハンドラが呼ばれる
    */
    signal(SIGINT,signal_handler);
    signal(SIGQUIT,signal_handler);
    while (1)
    {
        input = readline(">");
        if (input == NULL)
            break;
        if (input == NULL)
            printf("\n");
        free(input);
    }
    
}
/*
gcc signal.c -lreadline -L $(brew --prefix readline)/lib -I $(brew --prefix readline)/include
$(brew --prefix readline)/{include,lib}

readlineの仕様
*/

