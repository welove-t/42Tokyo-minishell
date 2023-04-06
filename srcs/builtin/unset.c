/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:56:13 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/06 21:01:56 by susasaki         ###   ########.fr       */
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

    if (strchr(str,'=') != NULL)
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