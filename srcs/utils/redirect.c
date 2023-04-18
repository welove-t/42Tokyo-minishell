/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:37:22 by terabu            #+#    #+#             */
/*   Updated: 2023/04/18 19:28:57 by susasaki         ###   ########.fr       */
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
	char 	*exp_tmp;
	char 	*new_word;
	new_word = NULL;
	exp_tmp = NULL;
	char 	*str;

	if (redir == NULL || redir->kind != ND_REDIR_HEREDOC)
		return ;
	while (1)
	{
		buff = readline("heredoc> ");
		if (buff == NULL)
			break;
		str = buff;
		if (!strcmp(str, redir->delimiter->word))
			break ;
		while (*str)
		{
			if (*str == DOLLAR_SIGN)
			{
				str++;
				// printf("*str = %c\n",*str);
				if (*str == '?')
				{
					append_char(&exp_tmp, *str);
					str++;
					// printf("if (*str == '?')に通った\n");
				}
				else
				{
					while(*str != ' ' && *str != '\t' &&
						*str != '\'' && *str != '\"' && *str != '\0')
					{
						append_char(&exp_tmp, *str);
						str++;
						// printf("whileが回った\n");
					}
				}
				printf("exp_tmp = %s\n",exp_tmp);
				// 環境変数を展開
				expand_env(&new_word, exp_tmp);
				if (exp_tmp != NULL)
				{
					free(exp_tmp);
					exp_tmp = NULL;
				}
				int i;
				i = 0;
				printf("new_word = %s\n",new_word);
				while (new_word[i] != '\0')
				{
					write(redir->filefd, &new_word[i],1);
					i++;
				}
			}
			else
			{
				write(redir->filefd, str++,1);
			}
		}
		// write(redir->filefd, buff, strlen(buff));
		write(redir->filefd, "\n", 1);
		free (buff);
		buff = NULL;
	}
	if (buff != NULL)
		free(buff);
}
