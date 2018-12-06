#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int usr1 = 0;
int usr2 = 0;

void signal_handler(int signo)
{
    if (signo == SIGUSR1)
    {
        usr1++;
    }
    else if (signo == SIGUSR2)
    {
        usr2++;
    }
    else if (signo == SIGTERM)
    {
        printf("%d %d\n", usr1, usr2);
        exit(0);
    }
}

int main()
{
    if (signal(SIGUSR1, signal_handler) == SIG_ERR)
        printf("\ncan't catch SIGUSR1\n");

    if (signal(SIGUSR2, signal_handler) == SIG_ERR)
        printf("\ncan't catch SIGUSR2\n");

    if (signal(SIGTERM, signal_handler) == SIG_ERR)
        printf("\ncan't catch SIGSTOP\n");

    while (1)
        sleep(1);

    return 0;
}
