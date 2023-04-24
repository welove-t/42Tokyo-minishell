/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:58:24 by terabu            #+#    #+#             */
/*   Updated: 2023/04/24 19:06:24 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_cmd(char *cmd)
{
	perror_prefix();
	if (ft_strchr(cmd, '/'))
	{
		put_error_msg(cmd);
		put_error_msg_endl(": No such file or directory");
	}
	else
	{
		put_error_msg(cmd);
		put_error_msg_endl(": command not found");
	}
	exit(1);
}
