/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:12:34 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/30 15:28:42 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler_waiting_input(int sig)
{
	printf("test\n");
	printf("sig = %d\n", sig);
	if (sig == SIGINT)
	{
		signal(SIGINT, SIG_DFL);
		g_global.status = 130;
		signal(SIGINT, signal_handler_waiting_input);
	}
	else if (sig == SIGQUIT)
	{
		signal(SIGQUIT, SIG_DFL);
		g_global.status = 131;
		signal(SIGQUIT, signal_handler_waiting_input);
	}
}
