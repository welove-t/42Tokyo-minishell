
#include "../../includes/minishell.h"

static int monitor_signal(void)
{
	// printf("monitor_signal\n");
	if (g_status == 1)
	{
		// printf("rl_done = 0\n");
		rl_done = 1;
	}
	else
	{
		rl_done = 0;
	}
	//0だと終了
	return 0;
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
	g_status = 0;
	rl_done = 0;
	// heredoc処理用にシグナルハンドラを設定
    signal(SIGINT, signal_handler_heredoc);
	while (g_status != 1)
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
		signal(SIGQUIT, signal_handler);
		// write(redir->filefd, "\n", 1);
		free (buff);
		buff = NULL;
	}
	/*
	signal(SIGINT,シグナルハンドラ)が2つ使用されている場合、最後に設定した
	シグナルハンドラが優先されるため、heredocを閉じるときにmainの方に戻してあげる。*/
	// printf("シグナルハンドラをsignal_handlerに戻す\n");
	signal(SIGINT, signal_handler);
	if (buff != NULL)
		free(buff);
}
