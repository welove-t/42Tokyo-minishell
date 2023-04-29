/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:11:08 by terabu            #+#    #+#             */
/*   Updated: 2023/04/27 21:10:50 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*heap;
	size_t	len_s1;
	size_t	len_s2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s2 == NULL || *s2 == '\0')
		return (ft_strdup(s1));
	if (s1 == NULL || *s1 == '\0')
		return (ft_strdup(s2));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	heap = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (heap == NULL)
		return (NULL);
	heap[0] = '\0';
	ft_strlcat(heap, s1, len_s1 + 1);
	ft_strlcat(heap, s2, len_s1 + len_s2 + 1);
	return (heap);
}
