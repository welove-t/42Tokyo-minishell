/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:11:30 by terabu            #+#    #+#             */
/*   Updated: 2023/04/27 21:09:56 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*heap;
	size_t	region;

	if (count == 0 || size == 0)
		return (ft_calloc(1, 1));
	region = count * size;
	if (count != region / size)
		return (NULL);
	heap = malloc(region);
	if (heap == NULL)
		return (NULL);
	ft_bzero(heap, region);
	return (heap);
}
