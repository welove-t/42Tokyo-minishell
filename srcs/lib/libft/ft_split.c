/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:11:19 by terabu            #+#    #+#             */
/*   Updated: 2022/11/01 12:45:56 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	split_count(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s == '\0')
			break ;
		while (*s != c && *s != '\0')
			s++;
		cnt++;
	}
	return (cnt);
}

static char	**ft_free(char **heap, size_t index)
{
	size_t	i;

	i = 0;
	while (i < index)
	{
		free(heap[i]);
		i++;
	}
	free(heap);
	return (NULL);
}

static char	**set_split(char const *s, char c, size_t cnt, char **heap)
{
	char	*end;
	size_t	i;

	i = 0;
	end = (char *)s;
	while (*s && i < cnt)
	{
		while (*s == c && *s != '\0')
		{
			s++;
			end++;
		}
		if (*s == '\0')
			break ;
		while (*end != c && *end != '\0')
			end++;
		heap[i] = ft_substr(s, 0, end - s);
		if (heap[i] == NULL)
			return (ft_free(heap, i));
		i++;
		s = end;
	}
	heap[i] = NULL;
	return (heap);
}

char	**ft_split(char const *s, char c)
{
	char	**heap;
	size_t	cnt;

	if (s == NULL)
		return (NULL);
	cnt = split_count(s, c);
	heap = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (heap == NULL)
		return (NULL);
	heap = set_split(s, c, cnt, heap);
	return (heap);
}
