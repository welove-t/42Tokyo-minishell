/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:11:24 by terabu            #+#    #+#             */
/*   Updated: 2022/11/01 12:45:56 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	digit(long n)
{
	size_t	cnt;

	if (n > 0)
		cnt = 0;
	else
	{
		cnt = 1;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

static void	set_num(char *heap, long n, size_t cnt)
{
	int	flg;

	if (n < 0)
	{
		flg = 1;
		n *= -1;
		heap[0] = '-';
	}
	else
		flg = 0;
	heap[cnt] = '\0';
	while (0 < cnt--)
	{
		if (cnt == 0 && flg == 1)
			break ;
		heap[cnt] = n % 10 + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*heap;
	size_t	cnt;

	cnt = digit((long)n);
	heap = (char *)malloc(sizeof(char) * (cnt + 1));
	if (heap == NULL)
		return (NULL);
	set_num(heap, (long)n, cnt);
	return (heap);
}
