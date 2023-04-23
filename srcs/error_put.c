/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:11:54 by terabu            #+#    #+#             */
/*   Updated: 2023/04/23 16:40:44 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	put_error_msg(char *error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
}

void	put_error_msg_endl(char *error_msg)
{
	ft_putendl_fd(error_msg, STDERR_FILENO);
}

void	put_error_char(char c)
{
	ft_putchar_fd(c, STDERR_FILENO);
}
