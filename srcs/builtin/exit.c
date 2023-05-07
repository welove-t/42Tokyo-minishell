/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:49:00 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/05 21:03:18 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	int_overflow__check(char *str, long *num)
{
	int	flag;
	int	i;
	unsigned long long tmp_ll;

	i = 0;
	flag = 1;
	tmp_ll  = 0;
	if (str[i] == '-')
	{
		flag = -1;
		i++;
	}
	else if(str[i] == '+')
		i++;
	while(str[i] == ' ' || str[i] == '\t')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		tmp_ll *= 10;
		tmp_ll += str[i] - '0';
		i++;
	}
	while(str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		return (1);
	// ullを使う事で、unsigned long longを明示的にに示す
	if ((LONG_MAX < tmp_ll && flag == 1) || 9223372036854775808ull < tmp_ll)
		return (1);
	tmp_ll *= flag;
	*num = tmp_ll;
	return (0);
}

static void	bi_single_exit_multiple(char *str)
{
	long	num;

	num = 0;
	if (int_overflow__check(str, &num) == 1)
	{
		put_error_msg_endl("exit: numeric argument required");
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

static void	bi_exit_multiple(char *str)
{
	long	num;

	num = 0;
	if (int_overflow__check(str, &num) == 1 || *str == '\0')
	{
		put_error_msg_endl("exit: numeric argument required");
		exit(255);
	}
	return ;
}

int	bi_exit(char **argv)
{
	if (argv[1] == NULL)
	{
		printf("exit\n");
		exit(g_global.status);
	}
	bi_exit_multiple(argv[1]);
	if (argv[1] && argv[2])
	{
		if (argv[1])
			bi_exit_multiple(argv[1]);
		if (argv[2])
		{
			put_error_msg_endl("exit: too many arguments");
			g_global.status = 1;
			return (0);
		}
		else
		{
			g_global.status = 1;
			exit(g_global.status);
		}
	}
	if (argv[1])
		bi_single_exit_multiple(argv[1]);
	return (0);
}
