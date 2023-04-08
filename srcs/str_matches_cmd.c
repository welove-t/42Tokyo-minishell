#include "../includes/minishell.h"


/*
TODO:
引数には単語だけ渡したほうがいい。
前後のスペースなどは除去する。コマンドがその単語だけか判断するために、
終端文字を判断材料にする。
例)
OK: cd
KO: cda
KO: cdbac
*/
void line_matches_cmd(char *line)
{
/*
main.cで記述したグローバル変数を使用したいため
extern宣言する
*/
	char	**cmd_line = NULL;
	t_token	*token;
	t_node	*node;


//自作builtinコマンドを試すだけなら、ここにif文を書いて関数を呼ぶ


	token = tokenize(line);
	node =	parse(token);
	expand(node);

	cmd_line = token_list_to_array(node->args);
	cmd_line[0] = get_cmd_array(ft_strtrim(cmd_line[0], " "));

	if (cmd_line != NULL)
	{
		if (execve(cmd_line[0], cmd_line, environ) == -1)
		{
			// printf("\x1b[31mError: execve()\x1b[0m\n");
		}
	}
	// else
		// printf("bash: %s: command not found\n",line);


//     if (strncmp("cd", line, 2) == 0)
//     {
//         printf("\x1b[32m文字列が\"cd\"と一致してます\x1b[0m\n");
//     }
//     else if (strncmp("echo", line, 4) == 0)
//     {
//         bi_echo(line);
//     }
//     else if (strncmp("env", line, 3) == 0)
//     {
//         printf("\x1b[32m文字列が\"env\"と一致してます\x1b[0m\n");
//     }
//     else if (strncmp("exit", line, 4) == 0)
//     {
//         printf("\x1b[32m文字列が\"exit\"と一致してます\x1b[0m\n");
//     }
//     else if (strncmp("export", line, 6) == 0)
//     {
//         printf("\x1b[32m文字列が\"export\"と一致してます\x1b[0m\n");
//     }
//     else if (strncmp("pwd", line, 3) == 0)
//     {
//         if (bi_pwd() == -1)
//             printf("\x1b[31m Error pwd \x1b[0m\n");
//     }
//     else if (strncmp("unset", line, 5) == 0)
//     {
//         printf("\x1b[32m文字列が\"unset\"と一致してます\x1b[0m\n");
//     }
//     /*
//     execveを使う
// 	ビルトインコマンドを除くシステムコマンドは、execveでpath指定して実行する。
// 	bult in cmd だけ、その処理を書いている関数を渡してあげる。
//     */
//    // TODO:システムコマンドだった場合

//    else if (cmd_line != NULL)
//    {
//        if (execve(cmd_line[0], cmd_line, environ) == -1)
//        {
//            printf("\x1b[31mError: execve()\x1b[0m\n");
//        }
//    }
//    else
//    {
//        printf("bash: %s: command not found\n",line);
//    }
	return ;
}
