/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:15:06 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/03 16:44:24 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	monitor_signal(void)
{
	if (g_global.status == 1)
		rl_done = 1;
	//0だと終了
	return (0);
}

static void	process_heredoc_line(char *str, t_node *redir,t_environ *env)
{
	char	*new_word;

	new_word = NULL;
	while (*str)
	{
		if (*str == DOLLAR_SIGN)
		{
			dollar_sign(&str, &new_word,env);
			while (*new_word)
				do_write(redir->file_fd, new_word++, 1);
			if (new_word)
			{
				new_word = NULL;
				free(new_word);
			}
		}
		else
			do_write(redir->file_fd, str++, 1);
	}
	do_write(redir->file_fd, "\n", 1);
}

void	do_heredoc(t_node *redir,t_environ *env)
{
	char	*buff;

	if (redir == NULL || redir->kind != ND_REDIR_HEREDOC)
		return ;
	g_global.status = 0;
	rl_done = 0;
	// heredoc処理用にシグナルハンドラを設定
	rl_event_hook = monitor_signal;
	signal(SIGINT, signal_handler_heredoc);
	while (g_global.status != 1 || g_global.flg_redir != 1)
	{
		buff = readline("heredoc> ");
		if (buff == NULL)
			break ;
		if (!ft_strcmp(buff, redir->delimiter->word))
			break ;
		process_heredoc_line(buff, redir,env);
		free(buff);
		buff = NULL;
	}
	/*
	signal(SIGINT,シグナルハンドラ)が2つ使用されている場合、最後に設定した
	シグナルハンドラが優先されるため、heredocを閉じるときにmainの方に戻してあげる。*/
	// printf("シグナルハンドラをsignal_handlerに戻す\n");
	rl_event_hook = NULL;
	signal(SIGINT, signal_handler);
	if (buff != NULL)
		free(buff);
}

void	delete_heredoc(char *filename)
{
	if (!access(filename, R_OK))
		do_unlink(filename);
}

void	loop_node_delete_heredoc(t_node *node)
{
	t_node	*tmp;

	if (node == NULL)
		return ;
	tmp = node;
	while (tmp)
	{
		if (tmp->kind == ND_REDIR_HEREDOC && tmp->filename)
			delete_heredoc(tmp->filename->word);
		tmp = tmp->redirects;
	}
	loop_node_delete_heredoc(node->next);
}

void	open_heredoc(t_node *redir, t_environ *env, size_t i)
{
	char	*ci;

	if (redir == NULL || g_global.flg_redir != 0
		|| redir->kind != ND_REDIR_HEREDOC)
		return ;
	ci = ft_itoa(i);
	redir->filename = new_token(NULL, TK_WORD);
	redir->filename->word = ft_strjoin(".heredoc", ci);
	free(ci);
	delete_heredoc(redir->filename->word);
	redir->file_fd = do_open_redir_append(redir->filename->word);
	if (redir->file_fd < 0)
	{
		g_global.flg_redir = 1;
		return ;
	}
	do_heredoc(redir, env);
	do_close(redir->file_fd);
	open_heredoc(redir->next, env, i);
}

void	check_heredoc(t_node *node, t_environ *env)
{
	size_t	i;
	t_node	*tmp;

	// if (get_node_cnt(node) > 1)
	// 	return ;
	i = 0;
	tmp = node;
	while (tmp)
	{
		open_heredoc(tmp->redirects, env, i);
		if (g_global.flg_redir != 0)
			break ;
		tmp = tmp->next;
		i++;
	}
}

