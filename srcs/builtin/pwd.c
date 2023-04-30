/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:15:31 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/30 19:47:42 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bi_pwd(void)
{
	char	path[4096];

	if (!getcwd(path, sizeof(path)))
		return (-1);
	printf("%s\n", path);
	return (0);
}
