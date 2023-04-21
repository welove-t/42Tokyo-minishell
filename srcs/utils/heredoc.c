
#include "../../includes/minishell.h"

static int monitor_signal(void)
{
    if (g_status == 1)
    {
        rl_done = 1;
    }
    else
    {
        rl_done = 0;
    }

    if (rl_done == 1)
    {
        rl_callback_handler_remove();
    }

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
	rl_catch_signals = 0;
	signal(SIGINT,signal_handler_heredoc);
	rl_event_hook = monitor_signal;
	
	while (g_status != 1)
	{
		if (g_status == 1)
		{
			// printf("g_status=1のため、breakする\n");
			free (buff);
			buff = NULL;
			break;
		}
		buff = readline("heredoc> ");
		str = buff;
		if (!strcmp(str, redir->delimiter->word))
        {
            // printf("delimiter文字が入力された\n");
			break ;
        }
		while (*str)
		{
            // printf("*str = %c\n",*str);
			if (*str == DOLLAR_SIGN)
			{
                dollar_sign(&str, &new_word);
                // printf("new_word = %s\n",new_word);
                // printf("*str = %c\n",*str);
                while(*new_word)
                {
                    write(redir->filefd, new_word++,1);
                }
                // str = new_word;
				if (new_word != NULL)
				{
                	new_word = NULL;
                	free(new_word);
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
	rl_event_hook = NULL;
	// printf("g_status = %d,rl_done = %d\n↑↑のため、heredocを終了\n",g_status,rl_done);
	rl_done = 0;
	// rl_catch_signals = 0;
	/*
	signal(SIGINT,シグナルハンドラ)が2つ使用されている場合、最後に設定した
	シグナルハンドラが優先されるため、heredocを閉じるときにmainの方に戻してあげる。*/
	signal(SIGINT, signal_handler);
	if (buff != NULL)
		free(buff);
}
