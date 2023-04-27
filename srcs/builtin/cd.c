/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:52:38 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/27 11:49:44 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	pathname_check(char *str)
{
	t_stat	tmp_stat;

	if (stat(str, &tmp_stat) == 0)
		return (0);
	else
		return (1);
}

static int	cd_home(void)
{
	char	*home_dir;

	home_dir = getenv("HOME");
	if (home_dir == NULL)
	{
		put_error_msg_endl("cd: could not get HOME directory");
		return (1);
	}
	if (chdir(home_dir) == -1)
	{
		put_error_msg_endl("cd: could not change to HOME directory");
		return (1);
	}
	return (0);
}

int	bi_cd(char **argv, int argc)
{
	if (argc == 1)
	{
		if (cd_home() == 1)
			return (-1);
	}
	else
	{
		if (pathname_check(argv[1]) == 0)
		{
			if (chdir(argv[1]) == -1)
			{
				put_error_msg_endl("cd: could not change to HOME directory");
				return (-1);
			}
		}
		else
			put_error_msg_endl("cd: No such file or directory");
	}
	return (0);
}
