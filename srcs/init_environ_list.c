#include "../includes/minishell.h"

extern char **environ;

int first_strlen(char *str)
{
        int i;
        int res;

        i = 0;
        res = 0;
        while(str[i] != '=' && str[i] != '\0')
        {
            res++;
            i++;
        }
        // printf("first_strlen = %d\n",res);
        return (res);
}

int latter_strlen(char *str)
{
        int i;
        int res;

        i = 0;
        res = 0;
        while(str[i] != '=' && str[i] != '\0')
        {
            i++;
        }
        i++;
        while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
        {
            i++;
            res++;
        }
        // printf("latter_strlen = %d\n",res);
        return (res);
}

void    init_environ_list(t_environ *env_list)
{
    int i;
    int j;
    int n;
    char **tmp;

    i = 0;
    j = 0;

    //環境変数environの値を直接変更したくないため
    
    tmp = environ;
    env_list = NULL; // ポインタ変数の初期化
    //環境変数を1行ずつ出力
    while (tmp[i] != NULL)
    {
        j = 0;
        n = 0;
        env_list=(t_environ *)malloc(sizeof(t_environ));
        if (!env_list)
            return ;
        env_list->name = (char *)malloc(sizeof(char) * (first_strlen(tmp[i]) + 1));
        if (!env_list->name)
        {
            free(env_list);
            return ;
        }
        while(tmp[i][j] != '=')
        {
            env_list->name[j] = tmp[i][j];
            j++;
        }
        // printf("%s",env_list->name);
        env_list->name[j] = '\0';
        j++;
        // printf("=");
        env_list->value=(char *)malloc(sizeof(char) * (latter_strlen(tmp[i]) + 1));
        if (!env_list->value)
        {
            free(env_list->name);
            free(env_list->value);
            return ;
        }
        while (tmp[i][j] != '\0')
        {
            env_list->value[n] = tmp[i][j];
            n++;
            j++;
        }
        env_list->value[n] = '\0';
        // printf("%s\n",env_list->value);
        env_list = env_list->next;
        i++;
    }
    env_list=(t_environ *)malloc(sizeof(t_environ));
    env_list->next = NULL;
}


// int main(void)
// {
//     t_environ env_list;
//     init_environ_list(&env_list);
//     // bl_env();
//     return 0;
// }