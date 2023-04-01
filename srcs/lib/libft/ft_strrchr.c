/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 07:19:31 by terabu            #+#    #+#             */
/*   Updated: 2022/11/01 12:45:56 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	cc;
	char	*return_p;

	cc = (char)c;
	return_p = NULL;
	while (*s != '\0')
	{
		if (*s == cc)
			return_p = (char *)s;
		s++;
	}
	if (cc == 0)
		return ((char *)s);
	if (return_p != NULL)
		return (return_p);
	else
		return (NULL);
}
