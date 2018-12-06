#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define BUFSIZE 100

int main(int argc, char const *argv[])
{
    pid_t pid = getpid();

    char path[80];
    sprintf(path, "%s%d%s", "/proc/", pid, "/stat");

    int fd;

    if ((fd = open(path, O_RDONLY)) < 0)
    {
        perror("get_pid");
    }

    char *c = (char *)calloc(BUFSIZE, sizeof(char));
    int sz = read(fd, c, BUFSIZE);

    c[sz] = '\0';

    int ppid;

    sscanf(c, "%*d %*s %*c %d", &ppid);
    printf("%d\n", ppid);

    if (close(fd) < 0)
    {
        perror("get_pid");
        exit(1);
    }

    return 0;
}
