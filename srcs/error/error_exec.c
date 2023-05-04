/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:58:24 by terabu            #+#    #+#             */
/*   Updated: 2023/05/04 17:08:12 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_cmd(char *cmd)
{
	perror_prefix();
	if (ft_strlen(cmd) == 1 && cmd[0] == '/')
	{
		put_error_msg(cmd);
		put_error_msg_endl(": No such file or directory");
		exit (126);
	}
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
	exit(127);
}

static void	error_dir(char *dir)
{
	put_error_msg(dir);
	put_error_msg_endl(": is a directory");
	exit(126);
}

void	error_file(char *filename)
{
	perror_prefix();
	put_error_msg(filename);
	put_error_msg(": ");
	put_error_msg_endl(strerror(errno));
}

void	error_exit(char *cmd)
{
	t_stat	cmd_stat;

	perror_prefix();
	if (stat(cmd, &cmd_stat) == 0)
	{
		if ((cmd_stat.st_mode & S_IFMT) == S_IFDIR)
			error_dir(cmd);
	}
	put_error_msg_endl(strerror(errno));
	exit(errno);
}
