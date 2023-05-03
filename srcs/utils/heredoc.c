/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:15:06 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/03 13:46:58 by terabu           ###   ########.fr       */
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
		if (!ft_strcmp(buff, redir->delimiter->word))
			break ;
		if (buff == NULL)
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

void	delete_heredoc(void)
{
	if (!access(".heredoc", R_OK))
		unlink(".heredoc");
}
