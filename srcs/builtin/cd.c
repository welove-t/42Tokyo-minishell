/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:52:38 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/25 17:58:32 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	pathname_check(char *str)
{
	struct stat	statBuf;

	//ディレクトリが存在する場合
	if (stat(str, &statBuf) == 0)
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
		printf("cd: could not get HOME directory\n");
		return (1);
	}
	if (chdir(home_dir) == -1)
	{
		printf("cd: could not change to HOME directory\n");
		return (1);
	}
	return (0);
}

void	bi_cd(char **argv, int argc)
{
	if (argc == 1)
	{
		if (cd_home() == 1)
			return ;
	}
	else
	{
		if (pathname_check(argv[1]) == 0)
		{
			if (chdir(argv[1]) == -1)
			{
				printf("cd: could not change to HOME directory\n");
				return ;
			}
		}
		else
			printf("cd: %s: No such file or directory\n", argv[1]);
	}
	return ;
}
