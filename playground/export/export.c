#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/param.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_environ
{
	char			*name;
	char 			*value;
	struct s_environ *next;
}	t_environ;

typedef struct s_envinfo
{
	//先頭ノード
	t_environ *head;
}	t_envinfo;

int first_strlen(char *str)
{
     printf("\x1b[32m~~~first_strlen~~~\x1b[0m\n");
        int i;

        i = 0;
        while(str[i] != '=' && str[i] != '\0')
        {
            i++;
        }
        printf("first_strlen = %d\n",i);
        return (i);
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

static void bi_env(t_environ *environ)
{
    printf("\x1b[32m~~~bi_env~~~\x1b[0m\n");
    t_environ *tmp;
    tmp = environ;
    // 環境変数を1行ずつ出力
    while (tmp != NULL)
    {
        // write(1, "NAME HERE!", 11);
        // write(1, tmp->name, 16);
        // write(1, "]NAME END!\n", 1);
        // printf("tmp->name = [%s][%p]\n",tmp->name, tmp->name);
        // printf("tmp->value = [%s][%p]\n",tmp->value, tmp->value);
        printf("%s=%s\n",tmp->name,tmp->value);
        tmp = tmp->next;
    }
}
//単体のとき
static void bi_only_export_env(t_environ *env)
{
    printf("~~bi_only_export_env~~\n");
    t_environ *print_env;

    print_env = env;
    printf("print_env->name = %s\n",print_env->name);
    printf("print_env->value = %s\n",print_env->value);
    printf("print_env->next->name = %s\n",print_env->next->name);
    printf("print_env->next->value = %s\n",print_env->next->value);
    while (print_env != NULL)
    {
        printf("declare -x %s",print_env->name);
        printf("=%s\n",print_env->value);
        print_env = print_env->next;
    }
    // env = env->next;
}

//最後尾にノードを追加する。
static void environ_nodeadd_back(t_environ *env, t_environ *new)
{
    printf("\x1b[32m~~~environ_nodeadd_back~~~\x1b[0m\n");

    if (env == NULL)
        return ;
    while (env->next != NULL)
    {
        // printf("i = %d\n",i);
        // i++;
        // printf("env = %p\n",env);
        env = env->next;
    }
    printf("new->name = %s\n",new->name);
    printf("new->value = %s\n",new->value);
    env->next = new;
    env = env->next;
    // env = tmp;
}

// static void environ_nodeadd_back(t_environ *env, t_environ *new)
// {
//     printf("\x1b[32m~~~environ_nodeadd_back~~~\x1b[0m\n");
//     t_environ *tmp;

//     // int i = 0;
//     tmp = env;
//     while (tmp->next != NULL)
//     {
//         // printf("i = %d\n",i);
//         // i++;
//         // printf("tmp = %p\n",tmp);
//         tmp = tmp->next;
//     }
//     printf("new->name = %s\n",new->name);
//     printf("new->value = %s\n",new->value);
//     tmp->next = new;
//     tmp = tmp->next;
//     printf("tmpにnewを代入後\n");
//     printf("tmp->name = %s\n",tmp->name);
//     printf("tmp->value = %s\n",tmp->value);
//     // env = tmp;
// }

//新たにノードを作る
static t_environ *environ_node_new(char *name, char *value)
{
    printf("\x1b[32m~~~environ_node_new~~~\x1b[0m\n");
    t_environ *new;

    new = (t_environ *)malloc(sizeof(t_environ));
    // new->name = (char *)malloc(strlen(name));
    // new->value = (char *)malloc(strlen(value));
    // printf("%s=%s\n",name,value);
    if (new == NULL)
        return (NULL);
    printf("name = %s\n",name);
    new->name = name; // name == "USAGI"
    new->value = value;
    printf("%s(%p)=%s(%p\n",new->name,new->name,new->value,new->value);
    new->next = NULL;
    return (new);
}

char    *make_name(char *str)
{
    char *name;
    int fir_len;
    fir_len = first_strlen(str);

    name = (char *)malloc(fir_len + 1);
    strncpy(name, str, fir_len);
    name[fir_len] = '\0';
    // if (str[fir_len] != '=')
    //     return ;
    return (name);
}

char    *make_value(char *str)
{
    char *value;
    int lat_len;
    int fir_len;

    fir_len = first_strlen(str);
    lat_len = latter_strlen(str);

    value = (char *)malloc(lat_len + 1);
    strncpy(value, str + fir_len + 1, lat_len);
    value[lat_len] = '\0';
    return (value);
}

//複数の場合分岐する。
static void bi_export(t_environ *env, char *str)
{
    printf("\x1b[32m~~~bi_export~~~\x1b[0m\n");
    char *name;
    char *value;
    int i;
    int j;
    t_environ *new;
    i = 0;
    j = 0;
    name = make_name(str);
    value = make_value(str);

    printf("name = %s\n",name);
    printf("value = %s\n",value);
    new = environ_node_new(name,value);
    environ_nodeadd_back(env, new);
    
    printf("\x1b[32m~~~hoge~~~\x1b[0m\n");
    t_environ *tmp;
    tmp = env;
    while (tmp != NULL)
    {
        // printf("i = %d\n",i);
        // i++;
        // printf("tmp = %p\n",tmp);
        tmp = tmp->next;
    }
    printf("new->name = %s\n",new->name);
    printf("new->value = %s\n",new->value);


}



extern char **environ;
static t_environ    *init_environ_list()
{
    int i;
    int j;
    int n;
    char *name;
    char *value;
    char **tmp;
    t_environ *env_list;
    t_envinfo *env_info;
    int flag;

    i = 0;
    flag = 0;
    //環境変数environの値を直接変更したくないため
    tmp = environ;
    env_list = NULL;
    env_info = (t_envinfo *)malloc(sizeof(t_envinfo));
    env_info->head = NULL;
    //環境変数を1行ずつ出力
    while (tmp[i] != NULL)
    {
        j = 0;
        n = 0;
        t_environ *new;

        name = (char *)malloc(sizeof(char) * (first_strlen(tmp[i]) + 1));
        value=(char *)malloc(sizeof(char) * (latter_strlen(tmp[i]) + 1));
        while(tmp[i][j] != '=')
        {
            name[j] = tmp[i][j];
            j++;
        }
        name[j] = '\0';
        j++;
        while (tmp[i][j] != '\0')
        {
            value[n] = tmp[i][j];
            n++;
            j++;
        }
        value[n] = '\0';
        new = environ_node_new(name, value);
        // new->name = (char *)malloc(sizeof(char) * (first_strlen(tmp[i]) + 1));
        new->name = name;
        printf("%s",new->name);
        // new->value= (char *)malloc(sizeof(char) * (latter_strlen(tmp[i]) + 1));
        new->value = value;
        printf("=%s\n",new->value);
        // printf("\x1b[31m空だ\x1b[0m\n");
        if (flag == 0)
        {
            env_list = new;
            env_info->head = env_list;
            flag = 1;
        }
        else
        {
            env_list->next = new;
            env_list = env_list->next;
        }
       
        i++;
    }
    env_list = NULL;
    printf("env_info->head->name = %s\n",env_info->head->name);
    env_list = env_info->head;
    printf("env_list->name = %s\n",env_list->name);
    return (env_list);
}
//TODO:指しているノードを先頭に戻す必要がる
int main(int argc,char **argv)
{
    t_environ *environ;

    // printf("main()\nenvlist = %p\n",&environ);
    environ = init_environ_list();
    // bi_env(environ);
    if (argc == 1)
    {
        // printf("\x1b[31m第2引数も書いてください\x1b[0m\n");
        bi_only_export_env(environ);
        return 0;
    }
    bi_export(environ,argv[1]);
    bi_env(environ);
    // memory leak確認
    // system("leaks a.out");
    return (0);
}
/*
//setenv関数を再実装する
static int ft_setenv(const char* name, const char* value, int overwrite)
{
    char **new_env;
    char *str;
    int i;
    int j;
    i = 0;
    j = 0;
    printf("~~~ ft_setenv() ~~~\n");
    if (!name)
    {
        printf("Failed to set environment variable.\n");
    }
    //+2は'='と'\0'。
    str = (char *)malloc(sizeof(char) * (strlen(name) + strlen(value) + 2));
    while (name[i] != '\0')
    {
        str[i] = name[i];
        i++;
    }
    str[i] = '=';
    i++;
    while (value[j] != '\0')
    {
        str[i] = value[j];
        i++;
        j++;
    }
    printf("str = %s\n",str);
    i = 0;
    j = 0;
    
    //環境変数の値は上書きする
    if (overwrite == 1)
    {
    //環境変数の数を数える
    while (environ[i] != NULL)
        i++;
    printf("environの数は%d個\nenviron[%d] = %s\n",i,i,environ[i]);
    printf("environ[%d] = %s\n",i - 1,environ[i - 1]);
    // 新しい配列を割り当て、環境変数のリストをコピーし、
    //最後に引数として渡された環境変数を追加する。
    new_env = (char **)malloc(sizeof(char *) * (i + 2));
    while (j < i)
    {
        new_env[j] = environ[j];
        j++;
    }
    printf("j = %d\n",j);
    new_env[j] = str;
    printf("new_env[%d] = %s\n",j,new_env[j]);
    j++;
    new_env[j] = NULL;
    environ = new_env;
    free(new_env);
    }

    return (0);
}
*/

/*
static t_environ    *init_environ_list(void)
{
    int i;
    int j;
    int n;
    char **tmp;
    t_environ *res;

    i = 0;
    j = 0;

    //環境変数environの値を直接変更したくないため
    tmp = environ;
    res = NULL; // ポインタ変数の初期化
    //環境変数を1行ずつ出力
    while (tmp[i] != NULL)
    {
        j = 0;
        n = 0;
        res=(t_environ *)malloc(sizeof(t_environ));
        if (!res)
            return (NULL);
        res->name = (char *)malloc(sizeof(char) * (first_strlen(tmp[i]) + 1));
        if (!res->name)
        {
            free(res);
            return (NULL);
        }
        while(tmp[i][j] != '=')
        {
            res->name[j] = tmp[i][j];
            j++;
        }
        printf("%s",res->name);
        res->name[j] = '\0';
        j++;
        printf("=");
        res->value=(char *)malloc(sizeof(char) * (latter_strlen(tmp[i]) + 1));
        if (!res->value)
        {
            free(res->name);
            free(res->value);
            return (NULL);
        }
        while (tmp[i][j] != '\0')
        {
            res->value[n] = tmp[i][j];
            n++;
            j++;
        }
        res->value[n] = '\0';
        printf("%s\n",res->value);
        res = res->next;
        i++;
    }
    res = (t_environ *)malloc(sizeof(t_environ));
    res->next = NULL;
    return (res);
}
*/