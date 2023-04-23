/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:56:13 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/23 14:33:53 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void bi_unset(t_environ *environ, char *str)
{
    int i;
    t_environ *tmp;
    int found;
    tmp = environ;

    found = 0;

    if (ft_strchr(str,'=') != NULL)
    {
        printf("unset: %s: invalid parameter name\n",str);
        return ;
    }
    while (tmp != NULL)
    {
        if (strcmp(tmp->name, str) == 0)
        {
            found = 1;
            break;
        }
        tmp = tmp->next;
    }

    // 環境変数が見つからない場合
    if (!found)
        return ;

    i = 0;
    while (environ != NULL)
    {
        if (environ->next->name == tmp->name)
        {
            environ->next = environ->next->next;
            break;
        }
        environ = environ->next;
    }
    return ;
}
