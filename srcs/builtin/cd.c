/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:52:38 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/24 19:49:29 by susasaki         ###   ########.fr       */
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

void	bi_cd(char **argv)
{
	char	buf[256];

	if (argv[1])
	{
		if (pathname_check(argv[1]) == 0)
		{
			getcwd(buf, sizeof(buf));
			/*
            printf("移動前: %s\n", buf);
            chdir(argv[1]);
            //移動しているか確認
            getcwd(buf, sizeof(buf));
            printf("移動後: %s\n", buf);
            */
			return ;
		}
		else
			printf("cd: %s: No such file or directory\n", argv[1]);
	}
	//TODO cdコマンド単体の処理をする
	return ;
}
