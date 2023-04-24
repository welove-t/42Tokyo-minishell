/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:38:03 by terabu            #+#    #+#             */
/*   Updated: 2023/04/24 20:30:12 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

size_t	get_node_cnt(t_node *node);

void	execution(t_node *node)
{
	size_t	cnt_node;
	pid_t	pid;

	cnt_node = get_node_cnt(node);
	//cmdが1つの場合
	if (cnt_node <= 1)
	{
		/*
		node->args->wordの中にcdなどのコマンドが入っている。
		fork()前にbuiltinか確認する。builtinだったら、forkしない
		*/
		//設定したビルトインコマンドがあったら、1が返ってくる
		if (search_bi_cmd(node) == 1)
			return ;
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid < 0)
			fatal_error("fork");
		else if (pid == 0)
			exec_cmd(node);
		else
			wait(NULL);
	}
	else
	{
		pipex(node, cnt_node);
		waitpid_pipex(node);
	}
	delete_heredoc();
}

void	exec_cmd(t_node *node)
{
	char	**cmd_line;

	open_redir_file(node->redirects);
	do_redirect(node->redirects);
	cmd_line = token_list_to_array(node->args);
	cmd_line[0] = get_cmd_array(ft_strtrim(cmd_line[0], " "));
	if (g_status != 1)
	{
		if (cmd_line[0] != NULL)
		{
			signal(SIGINT, SIG_DFL);
			if (execve(cmd_line[0], cmd_line, environ) == -1)
				fatal_error("execv");
		}
		else
			error_cmd(node->args->word);
	}
	reset_redirect(node->redirects);
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
