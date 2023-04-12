/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:21:01 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/11 16:36:13 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>

//ctrl-cが押された時に呼ばれるシグナルハンドラ
void ft_signal_handler(int sig)
{
    printf("Ctrl-Cが押された\n");
    printf("sig = %d\n",sig);
    exit(0);
}

int main(void)
{
    char *input;
    
    printf("pid = %d\n",getpid());
    
    /*
    シグナルハンドラを設定する
    SIGINT = ctrl-cが押された時にシグナルハンドラが呼ばれる
    */
    signal(SIGINT,ft_signal_handler);
    
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