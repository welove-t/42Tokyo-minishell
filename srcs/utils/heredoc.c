/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:15:06 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/27 13:15:06 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

static int	monitor_signal(void)
{
	if (g_status == 1)
		rl_done = 1;
	//0だと終了
	return (0);
}

static void	process_heredoc_line(char *str, t_node *redir)
{
	char	*new_word;

	new_word = NULL;
	while (*str)
	{
		if (*str == DOLLAR_SIGN)
		{
			dollar_sign(&str, &new_word);
			while (*new_word)
				write(redir->filefd, new_word++, 1);
			if (new_word)
			{
				new_word = NULL;
				free(new_word);
			}
		}
		else
			write(redir->filefd, str++, 1);
	}
	write(redir->filefd, "\n", 1);
}

void	do_heredoc(t_node *redir)
{
	char	*buff;
	char	*str;

	if (redir == NULL || redir->kind != ND_REDIR_HEREDOC)
		return ;
	g_status = 0;
	rl_done = 0;
	// heredoc処理用にシグナルハンドラを設定
	rl_event_hook = monitor_signal;
	signal(SIGINT, signal_handler_heredoc);
	while (g_status != 1)
	{
		buff = readline("heredoc> ");
		str = buff;
		if (!ft_strcmp(str, redir->delimiter->word))
			break ;
		// printf("buff = %s\n",buff);
		if (buff == NULL)
			break ;
		if (g_status == 1)
		{
			buff = NULL;
			free(buff);
			break ;
		}
		process_heredoc_line(str, redir);
		buff = NULL;
		free(buff);
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
