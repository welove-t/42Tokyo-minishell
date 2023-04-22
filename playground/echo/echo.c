/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:54:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/22 19:22:47 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO:./bash> echo -nnnn の処理をする
void bi_echo(char **argv)
{
    int nflag;
	int i;
	int j;
    nflag = 0;
	i = 1;
    if (argv[1] && argv[1][0] == '-')
    {
		j = 0;
        while(argv[1][j])
        {
			if (argv[1][j] == 'n')
            	nflag = 1;
			else
            	nflag = 0;
            j++;
        }
    }
	if (nflag == 1)
		i++;
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