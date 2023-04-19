/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:04:41 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/19 12:19:15 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

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
		// if (buff == NULL)
		// 	break;
		str = buff;
		if (!strcmp(str, redir->delimiter->word))
        {
            printf("delimiter文字が入力された\n");
			break ;
        }
		while (*str)
		{
            // printf("*str = %c\n",*str);
			if (*str == DOLLAR_SIGN)
			{
                dollar_sign(&str, &new_word);
                while(*new_word)
                {
                    write(redir->filefd, new_word++,1);
                }
                str = new_word;
                new_word = NULL;
                free(new_word);
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
