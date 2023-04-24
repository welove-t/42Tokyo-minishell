/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:54:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/23 19:51:33 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	check_nflag(char **argv, int *i)
{
	int	nflag;
	int	j;

	nflag = 0;
	j = 0;
	if (argv[1] && argv[1][0] == '-')
	{
		while (argv[1][j])
		{
			if (argv[1][j] == 'n')
				nflag = 1;
			else
				nflag = 0;
			j++;
		}
	}
	if (nflag == 1)
		(*i)++;
	return (nflag);
}

void	print_arguments(char **argv, int i, int nflag)
{
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (nflag == 0)
		printf("\n");
}

void	bi_echo(char **argv)
{
	int	nflag;
	int	i;

	i = 1;
	nflag = check_nflag(argv, &i);
	print_arguments(argv, i, nflag);
	return ;
}

int	main(int argc, char **argv)
{
	argc = 1;
	bi_echo(argv);
}
