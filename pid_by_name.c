#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int count = 0;
    const char *directory = "/proc";
    size_t taskNameSize = 1024;
    char *taskName = calloc(1, taskNameSize);

    DIR *dir = opendir(directory);

    if (dir)
    {
        struct dirent *de = 0;

        while ((de = readdir(dir)) != 0)
        {
            if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
                continue;

            int pid = -1;
            int res = sscanf(de->d_name, "%d", &pid);

            if (res == 1)
            {
                char cmdline_file[1024] = {0};
                sprintf(cmdline_file, "%s/%d/cmdline", directory, pid);

                FILE *cmdline = fopen(cmdline_file, "r");

                if (getline(&taskName, &taskNameSize, cmdline) > 0)
                {
                    if (strstr(taskName, "genenv") != 0)
                    {
                        count++;
                    }
                }

                fclose(cmdline);
            }
        }

        closedir(dir);
    }

    printf("%d\n", count);

    return 0;
}
