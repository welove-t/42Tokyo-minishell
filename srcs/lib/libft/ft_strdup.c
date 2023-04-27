/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:11:13 by terabu            #+#    #+#             */
/*   Updated: 2023/04/27 21:10:45 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*heap;
	size_t	len;

	len = ft_strlen(s) + 1;
	heap = (char *)malloc(sizeof(char) * len);
	if (heap == NULL)
		return (NULL);
	ft_memcpy(heap, s, len);
	return (heap);
}
