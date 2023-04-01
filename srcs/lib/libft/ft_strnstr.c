/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 07:19:28 by terabu            #+#    #+#             */
/*   Updated: 2022/11/01 12:45:56 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	slen;

	slen = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	if (len > 0)
	{
		while (*haystack != '\0' && slen <= len)
		{
			if (ft_strncmp(haystack, needle, slen) == 0)
				return ((char *)haystack);
			haystack++;
			len--;
		}
	}
	return (NULL);
}
