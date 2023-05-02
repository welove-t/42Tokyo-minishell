/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:34:05 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/02 12:38:46 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Debug用
static void	debug_write_endstatus(void)
{
	FILE	*fd;

	//ファイルを書き込みモードで開く
	// fd = fopen("/Users/tanakasubaru/Dropbox/42tokyo/Rank03/minishell/end_status.txt", "w");
	//相対パスの場合、そのプログラムを動かしている実行ファイルの場所からの指定
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
