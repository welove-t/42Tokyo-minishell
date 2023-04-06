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
    int i;

    i = 0;
    while(str[i] != '=' && str[i] != '\0')
    {
        i++;
    }
    return (i);
}

int latter_strlen(char *str)
{
    int i;
    int res;

    i = 0;
    res = 0;
    while(str[i] != '=' && str[i] != '\0')
        i++;
    if (str[i] == '\0')
        return (-1);
    i++;
    while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
    {
        i++;
        res++;
    }
    return (res);
}

static void bi_env(t_environ *environ)
{
    t_environ *tmp;
    tmp = environ;
    // 環境変数を1行ずつ出力
    while (tmp != NULL)
    {
        printf("%s",tmp->name);
        if (tmp->value != NULL)
            printf("=%s",tmp->value);
        printf("\n");
        tmp = tmp->next;
    }
}

//最後尾にノードを追加する。
static void environ_nodeadd_back(t_environ *env, t_environ *new)
{
    if (env == NULL)
        return ;
    while (env->next != NULL)
        env = env->next;
    env->next = new;
    env = env->next;
}

//新たにノードを作る
static t_environ *environ_node_new(char *name, char *value)
{
    t_environ *new;

    new = (t_environ *)malloc(sizeof(t_environ));
    if (new == NULL)
        return (NULL);
    new->name = name;
    new->value = value;
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
    return (name);
}

char    *make_value(char *str)
{
    char *value;
    int lat_len;
    int fir_len;

    fir_len = first_strlen(str);
    lat_len = latter_strlen(str);
    if (lat_len == -1)
        return NULL;
    value = (char *)malloc(lat_len + 1);
    strncpy(value, str + fir_len + 1, lat_len);
    value[lat_len] = '\0';
    return (value);
}

//単体のとき
static void bi_only_export_env(t_environ *env)
{
    t_environ *print_env;

    print_env = env;
    while (print_env != NULL)
    {
        printf("declare -x %s",print_env->name);
        if (print_env->value != NULL)
            printf("=%s",print_env->value);
        printf("\n");
        print_env = print_env->next;
    }
}

//複数の場合分岐する。
static void bi_export(t_environ *env, char *str)
{
    char *name;
    char *value;
    int i;
    int j;
    t_environ *new;
    i = 0;
    j = 0;
    name = make_name(str);
    value = make_value(str);
    new = environ_node_new(name,value);
    environ_nodeadd_back(env, new);
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

        name = make_name(tmp[i]);
        value = make_value(tmp[i]);
        new = environ_node_new(name, value);
        new->name = name;
        new->value = value;
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
    env_list = env_info->head;
    return (env_list);
}

int main(int argc,char **argv)
{
    t_environ *environ;
    environ = init_environ_list();
    (void)argv;
    (void)argc;
    if (argc == 1)
    {
        bi_only_export_env(environ);
        // memory leak確認
        // printf("\n\n\n");
        // system("leaks a.out");
        return 0;
    }
    bi_export(environ,argv[1]);
    bi_env(environ);
    // memory leak確認
    // printf("\n\n\n");
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