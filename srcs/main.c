/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:34:05 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/02 12:47:15 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Debug用: 終了ステータスをend_status.txtに書き込む
別プロセスでminishellの階層で下記のコマンドを実行
while true; do echo -n "Exit status: "; cat end_status.txt; sleep 1; done
*/
static void	debug_write_endstatus(void)
{
	FILE	*fd;

	fd = fopen("end_status.txt", "w");
	if (fd == NULL)
	{
		put_error_msg_endl("fopen");
		return ;
	}
	if (fprintf(fd, "%d\n", g_global.status) < 0)
	{
		put_error_msg_endl("fprintf");
		fclose(fd);
		return ;
	}
	fclose(fd);
}

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
		debug_write_endstatus();
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		else if (ft_strlen(input) == 0)
			;
		else
		{
			add_history(input);
			line_matches_cmd(input, environ);
		}
		free(input);
	}
	return (0);
}
