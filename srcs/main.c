/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:34:05 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/01 06:58:31 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char		*input;
	t_environ	*environ;

	g_global.syntax_error = false;
	signal(SIGQUIT, signal_handler);
	environ = init_environ_list();
	while (1)
	{
		signal(SIGINT, signal_handler);
		input = readline("minishell> ");
		// ctrl-Dが押されたら、EOFが代入され、NULLが入る。
		if (input == NULL)
			break ;
		else if (ft_strlen(input) == 0)
		{
			//Enterの場合は空文字が入る
		}
		else
		{
			add_history(input);
			line_matches_cmd(input, environ);
		}
		free(input);
	}
	return (0);
}
