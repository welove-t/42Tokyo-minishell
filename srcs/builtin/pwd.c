#include "../../includes/minishell.h"

int bi_pwd(void)
{
    //MAXPATHについて詳しく調べる
    char path[4096];
    //カレントディレクトリの場所をpathに代入
    if(!getcwd(path, sizeof(path)))
        return -1;
    printf("%s\n",path);
    return 0;
}