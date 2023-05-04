/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:34:05 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/04 17:34:04 by terabu           ###   ########.fr       */
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

static	bool	check_syntax_error(t_token *token, t_node *node, int flg)
{
	if (flg == 1 && g_global.syntax_error)
	{
		free_token(token);
		return (true);
	}
	else if (flg == 2 && g_global.syntax_error)
	{
		free_nodelist(node);
		return (true);
	}
	else if (flg == 3 && g_global.flg_redir)
	{
		loop_node_delete_heredoc(node);
		free_nodelist(node);
		g_global.flg_redir = 0;
		return (true);
	}
	else
		return (false);
}

void	line_matches_cmd(char *line, t_environ *environ)
{
	t_token	*token;
	t_node	*node;

	token = tokenize(line);
	node = NULL;
	if (check_syntax_error(token, node, 1))
		return ;
	node = parse(token);
	free_token(token);
	if (check_syntax_error(token, node, 2))
		return ;
	expand(node, environ);
	check_heredoc(node, environ);
	if (check_syntax_error(token, node, 3))
		return ;
	g_global.status = 0;
	execution(node, environ);
	free_nodelist(node);
	return ;
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
