/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:34:05 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/22 19:57:38 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	char *input;
	syntax_error = false;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		input = readline("minishell> ");
		// ctrl-Dが押されたら、EOFが代入され、whileから抜ける。
		if (input == NULL)
			break;
		if (input != NULL)
			add_history(input);
		if (input == NULL)
			printf("\n");
		else
		{
			signal(SIGINT, SIG_DFL);
			line_matches_cmd(input);
		}
		free(input);
	}
	return (0);
}
