#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void do_child()
{
    char *argv[3];
    char *filepath;

    printf("\x1b[32mThis is child(pid=%d)\x1b[0m\n",getpid());

    filepath = "/bin/ls";

    argv[0] = "ls";
    argv[1] = "-la";
    argv[2] = NULL;
    //ファイルパスで指定したプログラムを実行する
    execve(filepath,argv,environ);
}

int main(void)
{
    int child;
    int status;

    if ((child = fork()) < 0)
    {
        //エラーだった場合
        perror("fork");
        exit(1);
    }

    if (child == 0)
        do_child();
    else
    {
        if (wait(&status) == -1)
        {
             //エラーだった場合
             perror("wait");
             exit(1);
        }
        printf("\x1b[32mThe child (pid=%d) existed with status(%d).\x1b[0m\n",
            child, status);
    }
}