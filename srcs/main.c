/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:34:05 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/23 15:32:12 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	char *input;
	syntax_error = false;

	signal(SIGQUIT, signal_handler);
	while (1)
	{
		signal(SIGINT, signal_handler);
		// printf("待機中\n");
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
			line_matches_cmd(input);
		}
		free(input);
	}
	return (0);
}
