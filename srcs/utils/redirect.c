/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:37:22 by terabu            #+#    #+#             */
/*   Updated: 2023/04/27 18:23:13 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirection(t_node *redir)
{
	g_global.flg_redir = 0;
	open_redir_file(redir);
	if (g_global.flg_redir != 0)
		return ;
	do_redirect(redir);
}

int	stashfd(int fd)
{
	int	stashfd;

	stashfd = fcntl(fd, F_DUPFD, 10);
	if (stashfd < 0)
		fatal_error("fcntl");
	if (close(fd) < 0)
		fatal_error("close");
	return (stashfd);
}

void	open_redir_file(t_node *redir)
{

	if (redir == NULL)
		return ;
	if (redir->kind == ND_REDIR_OUT)
		redir->filefd = do_open_redir_out(redir->filename->word);
	else if (redir->kind == ND_REDIR_IN)
		redir->filefd = do_open_redir_in(redir->filename->word);
	else if (redir->kind == ND_REDIR_APPEND)
		redir->filefd = do_open_redir_append(redir->filename->word);
	else if (redir->kind == ND_REDIR_HEREDOC)
	{
		delete_heredoc();
		redir->filefd = do_open_redir_append(".heredoc");
		do_heredoc(redir);
		close(redir->filefd);
		redir->filefd = do_open_redir_in(".heredoc");
	}
	else
		assert_error("open_redir_file");
	if (redir->filefd < 0)
	{
		g_global.flg_redir = 1;
		return ;
	}
	// dprintf(STDOUT_FILENO, "before:filefd:%d\n", redir->filefd);
	// dprintf(STDOUT_FILENO, "before:targetfd:%d\n", redir->targetfd);
	// dprintf(STDOUT_FILENO, "before:stashedfd:%d\n", redir->stashed_targetfd);
	redir->filefd = stashfd(redir->filefd);
	// dprintf(STDOUT_FILENO, "after:filefd:%d\n", redir->filefd);
	// dprintf(STDOUT_FILENO, "after:targetfd:%d\n", redir->targetfd);
	// dprintf(STDOUT_FILENO, "after:stashedfd:%d\n", redir->stashed_targetfd);
	open_redir_file(redir->next);
}

void	do_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	if (redir->kind == ND_REDIR_OUT || redir->kind == ND_REDIR_IN \
		|| redir->kind == ND_REDIR_APPEND || redir->kind == ND_REDIR_HEREDOC)
	{
		redir->stashed_targetfd = stashfd(redir->targetfd);
		dup2(redir->filefd, redir->targetfd);
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
		close(redir->filefd);
		close(redir->targetfd);
		dup2(redir->stashed_targetfd, redir->targetfd);
	}
}
