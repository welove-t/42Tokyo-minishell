/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:15:31 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/06 17:16:10 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int bi_pwd(void)
{
    //MAXPATHについて詳しく調べる
    char path[4096];
    //カレントディレクトリの場所をpathに代入
    if(!getcwd(path, sizeof(path)))
        return -1;
    printf("%s\n",path);
    return 0;
}