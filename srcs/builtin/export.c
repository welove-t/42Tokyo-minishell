/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:50 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/05 21:52:41 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char    *make_name(char *str)
{
    char *name;
    int fir_len;
    fir_len = first_strlen(str);

    name = (char *)malloc(fir_len + 1);
    strncpy(name, str, fir_len);
    name[fir_len] = '\0';
    return (name);
}

static char    *make_value(char *str)
{
    char *value;
    int lat_len;
    int fir_len;

    fir_len = first_strlen(str);
    lat_len = latter_strlen(str);
    if (lat_len == -1)
        return NULL;
    value = (char *)malloc(lat_len + 1);
    strncpy(value, str + fir_len + 1, lat_len);
    value[lat_len] = '\0';
    return (value);
}

//単体のとき
void bi_only_export_env(t_environ *env)
{
    t_environ *print_env;

    print_env = env;
    while (print_env != NULL)
    {
        printf("declare -x %s",print_env->name);
        if (print_env->value != NULL)
            printf("=%s",print_env->value);
        printf("\n");
        print_env = print_env->next;
    }
}

//複数の場合分岐する。
void bi_export(t_environ *env, char *str)
{
    char *name;
    char *value;
    t_environ *new;
    name = make_name(str);
    value = make_value(str);
    new = environ_node_new(name,value);
    environ_nodeadd_back(env, new);
}