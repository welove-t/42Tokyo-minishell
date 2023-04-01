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
    extern char **environ;
    char *argv[] = {line,NULL};

    //空白とtabは読み飛ばす
    while (*line == ' ' || *line == '\t')
        line++;
    printf("line = %s\n",line);
    //cmdがある場合
    if (strncmp("cd", line, 2) == 0)
    {
        printf("\x1b[32m文字列が\"cd\"と一致してます\x1b[0m\n");
    }
    else if (strncmp("echo", line, 4) == 0)
    {
        bi_echo(line);
    }
    else if (strncmp("env", line, 3) == 0)
    {
        printf("\x1b[32m文字列が\"env\"と一致してます\x1b[0m\n");
    }
    else if (strncmp("exit", line, 4) == 0)
    {
        printf("\x1b[32m文字列が\"exit\"と一致してます\x1b[0m\n");
    }
    else if (strncmp("export", line, 6) == 0)
    {
        printf("\x1b[32m文字列が\"export\"と一致してます\x1b[0m\n");
    }
    else if (strncmp("pwd", line, 3) == 0)
    {
        if (bi_pwd() == -1)
            printf("\x1b[31m Error pwd \x1b[0m\n");
    }
    else if (strncmp("unset", line, 5) == 0)
    {
        printf("\x1b[32m文字列が\"unset\"と一致してます\x1b[0m\n");
    }
    /*
    execveを使う
	ビルトインコマンドを除くシステムコマンドは、execveでpath指定して実行する。
	bult in cmd だけ、その処理を書いている関数を渡してあげる。
    */
   // TODO:システムコマンドだった場合
   else if (strncmp("ls", line, 2) == 0)
   {
       if (execve("/bin/ls", argv, environ) == -1)
       {
           printf("\x1b[31mError: execve()\x1b[0m\n");
       }
   }
   else
   {
       printf("bash: %s: command not found\n",line);
   }
    return ;
}