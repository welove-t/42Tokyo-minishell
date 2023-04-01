#include "../../includes/minishell.h"

void bi_echo(char *str)
{
    printf("bi_echo\n");
    //echoという文字列を読み飛ばす
    while(*str != ' ' && *str != '\t' && *str != '\0')
        str++;
    while((*str == ' ' || *str == '\t') && *str != '\0')
        str++;
    
    while(*str != ' ' && *str != '\t' && *str != '\0')
    {
        printf("%c",*str);
        str++;
    }
    while((*str == ' ' || *str == '\t') && *str != '\0')
        str++;
    while (*str != '\0')
    {
        printf(" ");
        while(*str != ' ' && *str != '\t' && *str != '\0')
        {
            printf("%c",*str);
            str++;
        }
        while((*str == ' ' || *str == '\t') && *str != '\0')
        {
            str++;
        }
    }
    // printf("%s$",str);
    printf("\n");
    return ;
}