/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 07:19:03 by terabu            #+#    #+#             */
/*   Updated: 2022/11/01 12:45:56 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	setnum(char *s, int i)
{
	long	n;
	long	od;
	int		om;

	n = 0;
	while ('0' <= *s && *s <= '9')
	{
		n = (n * 10 + (*s++ - '0') * i);
		if (i < 0)
		{
			od = LONG_MIN / 10;
			om = (int)(LONG_MIN % 10 * -1);
			if ((n < od && *s != '\0') || (n == od && ((int)(*s - '0')) > om))
				return ((int)LONG_MIN);
		}
		else
		{
			od = LONG_MAX / 10;
			om = (int)(LONG_MAX % 10);
			if ((n > od && *s != '\0') || (n == od && ((int)(*s - '0')) > om))
				return ((int)LONG_MAX);
		}
	}
	return ((int)(n));
}

int	ft_atoi(const char *nptr)
{
	char		*str;
	int			sign;

	str = (char *)nptr;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	return (setnum(str, sign));
}
