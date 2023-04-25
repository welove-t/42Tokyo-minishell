/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:34:05 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/25 13:12:15 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*input;
	t_environ *environ;

	syntax_error = false;
	signal(SIGQUIT, signal_handler);
	//TODO: ここで環境変数を初期化する
	environ = init_environ_list();
	while (1)
	{
		signal(SIGINT, signal_handler);
		input = readline("minishell> ");
		// ctrl-Dが押されたら、EOFが代入され、whileから抜ける。
		if (input == NULL)
			break ;
		if (input != NULL)
			add_history(input);
		//TODO:このif文いらないかも
		if (input == NULL)
			printf("\n");
		else
		{
			line_matches_cmd(input,environ);
		}
		free(input);
	}
	return (0);
}
