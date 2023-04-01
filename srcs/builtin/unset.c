#include "../../includes/minishell.h"

void bi_unset(char *var_name)
{
    int i;
    int j;
    int name_len;
    extern char **g_environ;

    // 引数がNULLの場合、何もしない
    if (var_name == NULL)
        return ;
    name_len = strlen(var_name);

    i = 0;
    // 環境変数リストの各要素に対して
    while (g_environ[i] != NULL)
    {
        //引数(var_name)に環境変数(g_environ)があるかどうか
        //またその単語の後に'='が続いているか
        if (strncmp(var_name, g_environ[i], name_len) == 0
        && g_environ[i][name_len] == '=')
        {
            j = i;
            // 見つかったらリストから削除する
            while (g_environ[j] != NULL)
            {
                g_environ[j] = g_environ[j + 1];
                j++;
            }
            break;
        }
    }
}