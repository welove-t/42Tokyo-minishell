/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:11:13 by terabu            #+#    #+#             */
/*   Updated: 2022/10/17 13:52:19 by terabu           ###   ########.fr       */
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
