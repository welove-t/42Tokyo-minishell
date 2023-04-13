/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:54:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/13 12:19:24 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bi_echo(char **argv)
{
    int i;
    int nflag;

    nflag = 0;
    i = 1;
    if (argv[1])
    {
        if (strcmp(argv[i],"-n") == 0)
        {
            nflag = 1;
            i++;
        }
    }
    while (argv[i])
    {
        printf("%s",argv[i]);
        if(argv[i + 1])
            printf(" ");
        i++;
    }
    if (nflag == 0)
        printf("\n");
    return ;
}

int main(int argc, char **argv)
{
    argc = 1;
    bi_echo(argv);
}