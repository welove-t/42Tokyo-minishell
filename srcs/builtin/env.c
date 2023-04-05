/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:27:04 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/05 21:46:28 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void bi_env(t_environ *environ)
{
    t_environ *tmp;
    tmp = environ;
    // 環境変数を1行ずつ出力
    while (tmp != NULL)
    {
        printf("%s",tmp->name);
        if (tmp->value != NULL)
            printf("=%s",tmp->value);
        printf("\n");
        tmp = tmp->next;
    }
}



// void bl_env(void)
// {
//     //環境変数environの値を直接変更したくないため
//     char **tmp;
    
//     tmp = environ;
//     //環境変数を1行ずつ出力
//     while (*tmp != NULL)
//     {
//         printf("%s\n",*tmp);
//         tmp++;
//     }
// }

// int main(void)
// {
//     bl_env();
//     return 0;
// }