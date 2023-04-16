/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:37:22 by terabu            #+#    #+#             */
/*   Updated: 2023/04/16 11:45:13 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_heredoc(t_node *redir);

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
		redir->filefd = open(redir->filename->word, \
				O_WRONLY | O_CREAT | O_TRUNC, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (redir->kind == ND_REDIR_IN)
		redir->filefd = open(redir->filename->word, O_RDONLY);
	else if (redir->kind == ND_REDIR_APPEND)
		redir->filefd = open(redir->filename->word, \
				O_WRONLY | O_CREAT | O_APPEND, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (redir->kind == ND_REDIR_HEREDOC)
	{
		if (!access(".heredoc", R_OK))
			unlink(".heredoc");
		redir->filefd = open(".heredoc", O_WRONLY | O_CREAT | O_APPEND, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		do_heredoc(redir);
		close(redir->filefd);
		redir->filefd = open(".heredoc", O_RDONLY);
	}
	else
		assert_error("open_redir_file");
	redir->filefd = stashfd(redir->filefd);
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

void	do_heredoc(t_node *redir)
{
	char	*buff;

	if (redir == NULL || redir->kind != ND_REDIR_HEREDOC)
		return ;
	while (1)
	{
		buff = readline("> ");
		if (!buff)
			break ;
		if (!strcmp(buff, redir->delimiter->word))
			break ;
		write(redir->filefd, buff, strlen(buff));
		write(redir->filefd, "\n", 1);
		free (buff);
	}
	free(buff);
}
