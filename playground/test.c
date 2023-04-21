#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    while(1)
    {
        
    }
}


#define SIG_GET 0
#define SIG_SET 1

int    set_get_signal_status(int set_signal)
{
    static int sig_status;

    if (set_signal == SIG_GET)
        return (sig_status);
    sig_status = set_signal;
    return (0);
}

int    signal_status(int act, int signum)
{
    static int si
    if (act == SIG_GET)
        return (__GCC_ATOMIC_TEST_AND_SET_TRUEVAL)
}

void    signalhandeler(int sig)
{
    // g_signal = sig;
    set_get_signal_status(sig);
    printf("%d  \n", sig);
}

int    main()
{
    signal(SIGINT, signalhandeler);
    while (1)
    {
        // if (g_signal != 0)
        //     break;
        // if (g_signal == SIGINT)
        //     break;
        if (set_get_signal_status(SIG_GET) == SIGINT)
        {
            break;
        }

    }
    return (0);
}