
#include "../../includes/minishell.h"

static int monitor_signal(void)
{
	if (g_status == 1)
		rl_done = 1;
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
	rl_event_hook = monitor_signal;
	signal(SIGINT, signal_handler_heredoc);
	while (g_status != 1)
	{
		buff = readline("heredoc> ");
		str = buff;
		if (!ft_strcmp(str, redir->delimiter->word))
			break ;
		if (g_status == 1)
		{
			buff = NULL;
			free(buff);
			break;
		}
		while (*str)
		{
			if (*str == DOLLAR_SIGN)
			{
                dollar_sign(&str, &new_word);
                while(*new_word)
                    write(redir->filefd, new_word++,1);
				if (new_word)
				{
                	new_word = NULL;
                	free(new_word);
				}
			}
			else
				write(redir->filefd, str++,1);
		}
		write(redir->filefd, "\n", 1);
		buff = NULL;
		free (buff);
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
