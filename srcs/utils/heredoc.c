
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
		str = buff;
		if (!strcmp(str, redir->delimiter->word))
			break ;
		while (*str)
		{
            // printf("*str = %c\n",*str);
			if (*str == DOLLAR_SIGN)
			{
                dollar_sign(&str, &new_word);
                // printf("new_word = %s\n",new_word);
                // printf("*str = %c\n",*str);
                while(*new_word)
                    write(redir->filefd, new_word++,1);
                // str = new_word;
				if (new_word)
				{
                	free(new_word);
                	new_word = NULL;
				}
			}
			else
			{
				write(redir->filefd, str++,1);
			}
		}
		// write(redir->filefd, "\n", 1);
		free (buff);
		buff = NULL;
	}
	/*
	signal(SIGINT,シグナルハンドラ)が2つ使用されている場合、最後に設定した
	シグナルハンドラが優先されるため、heredocを閉じるときにmainの方に戻してあげる。*/
	signal(SIGINT, signal_handler);
	if (buff != NULL)
		free(buff);
}
