#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define BUF_SIZE 80000

size_t count_zeroes(const char *str);

int main(int argc, char *argv[])
{
    int len;
    char buf[BUF_SIZE];
    char params[30];

    FILE *f, *o;

    if (argc != 3)
    {
        printf("usage: makelog \"<command>\"\n");
        return -1;
    }

    sprintf(params, "%s %s", argv[1], argv[2]);

    f = popen(params, "r");
    if (f == NULL)
    {
        perror("error:\n");
        return -1;
    }

    while ((len = fread(buf, 1, BUF_SIZE, f)) != 0)
        ;
    unsigned int count = count_zeroes(buf);
    printf("%u\n", count);

    pclose(f);
    return 0;
}

size_t count_zeroes(const char *str)
{
    size_t count = 0;
    while (*str)
    {
        if (*str++ == '0')
            ++count;
    }

    return count;
}
