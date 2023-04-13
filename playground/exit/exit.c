/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:01:07 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/13 09:08:51 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

int g_status;

static int int_overflow__check(char *str, long *num)
{
    int flag;
    int i;
    i = 0;
    flag = 1;

    if (str[i] == '-')
    {
        flag = -1;;
        i++;
    }
    while ('0' <= str[i] && str[i] <= '9')
    {
        *num *= 10;
        *num += str[i] - '0';        
        i++;
    }
    if ((str[i] < '0' || '9' < str[i]) && str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
        return (1);
    *num *= flag;
    if (*num < INT_MIN || INT_MAX < *num)
        return (1);
    return (0);
}

static void bi_single_exit_multiple(char *str)
{
    long num;
    num = 0;
    
    if (int_overflow__check(str,&num) == 1)
    {
        printf("exit: %s: numeric argument required\n",str);
        exit(255);
    }
    if (num < 0)
    {
        num *= -1;
        printf("exit\n");
        exit(255 - num + 1);
    }
    else
    {
        printf("exit\n");
        exit(num);
    }
}
static void bi_exit_multiple(char *str)
{
    long num;
    num = 0;
    
    if (int_overflow__check(str,&num) == 1)
    {
        printf("exit: %s: numeric argument required\n",str);
        exit(255);
    }
    return ;
}

//TODO:tokenの引数を貰う
//TODO:グローバル変数を導入して実装する
static void bi_exit(char **argv)
{
    g_status = 0;
    if (argv[1] == NULL)
    {
        printf("exit\n");
        exit(g_status);
    }
    if (argv[1] && argv[2])
    {
        if (argv[1])
        {
            bi_exit_multiple(argv[1]);
        }
        printf("exit: too many arguments\n");
        g_status = 1;
        exit(1) ;
    }
    if (argv[1])
    {
        bi_single_exit_multiple(argv[1]);
    }
}

int main(int argc, char **argv)
{
    argc = 1;
    bi_exit(argv);
    printf("Goodbye!\n");
    return 0;
}
