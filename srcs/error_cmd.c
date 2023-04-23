/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:58:24 by terabu            #+#    #+#             */
/*   Updated: 2023/04/23 13:45:50 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_cmd(char *cmd)
{
	perror_prefix();
	if (ft_strchr(cmd, '/'))
		dprintf(STDERR_FILENO, "%s: No such file or directory\n", cmd);
	else
		dprintf(STDERR_FILENO, "%s: command not found\n", cmd);
	exit(1);
}
