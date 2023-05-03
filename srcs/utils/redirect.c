/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:37:22 by terabu            #+#    #+#             */
/*   Updated: 2023/05/03 12:25:46 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirection(t_node *redir,t_environ *env)
{
	g_global.flg_redir = 0;
	open_redir_file(redir,env);
	if (g_global.flg_redir != 0 || g_global.status == 1)
		return ;
	do_redirect(redir);
}

int	stashfd(int fd)
{
	int	tmp_fd;

	tmp_fd = dup(fd);
	if (tmp_fd < 0)
		fatal_error("fcntl");
	do_close(fd);
	return (tmp_fd);
}

void	open_redir_file(t_node *redir,t_environ *env)
{
	if (redir == NULL || g_global.flg_redir != 0)
		return ;
	if (redir->kind == ND_REDIR_OUT)
		redir->file_fd = do_open_redir_out(redir->filename->word);
	else if (redir->kind == ND_REDIR_IN)
		redir->file_fd = do_open_redir_in(redir->filename->word);
	else if (redir->kind == ND_REDIR_APPEND)
		redir->file_fd = do_open_redir_append(redir->filename->word);
	else if (redir->kind == ND_REDIR_HEREDOC)
	{
		delete_heredoc();
		redir->file_fd = do_open_redir_append(".heredoc");
		do_heredoc(redir,env);
		do_close(redir->file_fd);
		redir->file_fd = do_open_redir_in(".heredoc");
	}
	else
		assert_error("open_redir_file");
	if (redir->file_fd < 0)
	{
		g_global.flg_redir = 1;
		return ;
	}
	redir->file_fd = stashfd(redir->file_fd);
	open_redir_file(redir->next,env);
}

void	do_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	if (redir->kind == ND_REDIR_OUT || redir->kind == ND_REDIR_IN \
		|| redir->kind == ND_REDIR_APPEND || redir->kind == ND_REDIR_HEREDOC)
	{
		redir->stacktmp_fd = stashfd(redir->target_fd);
		do_dup2(redir->file_fd, redir->target_fd);
	}
	else
		assert_error("do_redirect");
	do_redirect(redir->next);
}

// リストの逆からクローズ
// 最終的に標準入力・出力に戻す
void	reset_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	reset_redirect(redir->next);
	if (redir->kind == ND_REDIR_OUT || redir->kind == ND_REDIR_IN \
		|| redir->kind == ND_REDIR_IN || redir->kind == ND_REDIR_HEREDOC)
	{
		do_close(redir->file_fd);
		do_close(redir->target_fd);
		do_dup2(redir->stacktmp_fd, redir->target_fd);
	}
}
