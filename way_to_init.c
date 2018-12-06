#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <dirent.h>

int getppid(int pid)
{
    char fname[255];
    char buf[255];

    sprintf(fname, "/proc/%i/status", pid);
    FILE *f = fopen(fname, "r");

    int pppid;

    while (fgets(buf, sizeof(buf), f))
    {
        char tag[255];
        pppid = -1;
        sscanf(buf, "%s\t%i", tag, &pppid);
        if (strcmp(tag, "PPid:") == 0)
            break;
    }

    fclose(f);
    return pppid;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return -1;

    int pid, ppid;

    sscanf(argv[1], "%i", &pid);
    printf("%i\n", pid);

    ppid = getppid(pid);

    while (ppid != 1)
    {
        printf("%i\n", ppid);
        ppid = getppid(ppid);
    }

    printf("1\n");

    return 0;
}
