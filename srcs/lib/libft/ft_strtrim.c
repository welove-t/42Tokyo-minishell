/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:11:02 by terabu            #+#    #+#             */
/*   Updated: 2022/11/01 12:45:56 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*end_point(char const *start, char const *end, char const *set)
{
	char	*tmp_set;

	while (end != start)
	{
		tmp_set = (char *)set;
		while (*tmp_set != '\0' && *tmp_set != *end)
			tmp_set++;
		if (*tmp_set == '\0')
			break ;
		end--;
	}
	return ((char *)end);
}

static char	*start_point(char const *s1, char const *set)
{
	char	*tmp_set;

	while (*s1)
	{
		tmp_set = (char *)set;
		while (*tmp_set != '\0' && *tmp_set != *s1)
			tmp_set++;
		if (*tmp_set == '\0')
			break ;
		s1++;
	}
	return ((char *)s1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*heap;
	char	*start;
	char	*end;
	size_t	len;

	if (s1 == NULL)
		return (NULL);
	if (*s1 == '\0')
		return (ft_strdup(""));
	start = start_point(s1, set);
	end = end_point(start, ((char *)s1 + ft_strlen(s1) - 1), set);
	if (start > end)
		return (ft_strdup(""));
	len = end - start + 1;
	heap = (char *)malloc(sizeof(char) * (len + 1));
	if (heap == NULL)
		return (NULL);
	ft_memcpy(heap, start, len);
	heap[len] = '\0';
	return (heap);
}
