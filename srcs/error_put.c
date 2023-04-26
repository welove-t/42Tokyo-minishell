/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:11:54 by terabu            #+#    #+#             */
/*   Updated: 2023/04/26 16:32:14 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//fd[2]にエラー出力
void	put_error_msg(char *error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
}

//fd[2]にエラー出力(改行あり)
void	put_error_msg_endl(char *error_msg)
{
	ft_putendl_fd(error_msg, STDERR_FILENO);
}

void	put_error_char(char c)
{
	ft_putchar_fd(c, STDERR_FILENO);
}
