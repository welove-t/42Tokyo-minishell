/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:38:03 by terabu            #+#    #+#             */
/*   Updated: 2023/05/01 14:50:21 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	get_node_cnt(t_node *node);

void	execution(t_node *node, t_environ *environ)
{
	size_t	cnt_node;
	pid_t	pid;
	int		wstatus;

	wstatus = 0;
	cnt_node = get_node_cnt(node);
	//cmdが1つの場合
	if (cnt_node <= 1)
	{
		/*
		node->args->wordの中にcdなどのコマンドが入っている。
		fork()前にbuiltinか確認する。builtinだったら、forkしない
		*/
		//設定したビルトインコマンドがあったら、0が返ってくる
		if (search_bi_cmd(node, environ) != 1)
			return ;
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid < 0)
			fatal_error("fork");
		else if (pid == 0)
			exec_cmd(node);
		else
			wait(&wstatus);
	}
	else
	{
		pipex(node, cnt_node, environ);
		waitpid_pipex(node, &wstatus);
	}
	finalize(wstatus);
	// g_global.status = WEXITSTATUS(wstatus);
	// delete_heredoc();
}

// void	printf_argv(char **argv)
// {
// 	for (int i = 0; argv[i]; i++)
// 	{
// 		dprintf(2, "argv[%d]:%s\n", i, argv[i]);
// 	}
// }

void	exec_cmd(t_node *node)
{
	char	**cmd_line;

	redirection(node->redirects);
	if (g_global.flg_redir != 0)
		exit(EXIT_FAILURE);
	cmd_line = token_list_to_array(node->args);
	// printf_argv(cmd_line);
	// dprintf(2, "status:%d\n", g_global.status);
	cmd_line[0] = get_cmd_array(cmd_line[0]);
	if (g_global.status != 1)
	{
		if (cmd_line[0] != NULL)
		{
			if (execve(cmd_line[0], cmd_line, environ) == -1)
				error_exit(cmd_line[0]);
				// fatal_error("execv");
		}
		else
			error_cmd(node->args->word);
	}
	// reset_redirect(node->redirects);
}

size_t	get_node_cnt(t_node *node)
{
	size_t	cnt;

	cnt = 0;
	while (node != NULL)
	{
		cnt++;
		node = node->next;
	}
	return (cnt);
}
