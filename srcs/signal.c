/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:30:37 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/22 14:00:05 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void signal_backslash()
{
   return ;
}

static void signal_c_cmd()
{
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
}

void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		signal_c_cmd();
	}
	else if (sig == SIGQUIT)
	{
		signal_backslash();
	}
	return ;
}
