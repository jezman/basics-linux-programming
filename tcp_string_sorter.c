#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int cmpfunc(const void *a, const void *b)
{
    return *(char *)b - *(char *)a;
}

#define BUFFER_SIZE 1024
#define on_error(...)                 \
    {                                 \
        fprintf(stderr, __VA_ARGS__); \
        fflush(stderr);               \
        exit(1);                      \
    }

void AlphabetSoup(char str[])
{
    qsort(str, (size_t)strlen(str), (size_t)sizeof(char), cmpfunc);
    printf("%s\n", str);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        on_error("Usage: %s [port]\n", argv[0]);

    int port = atoi(argv[1]);
    int server_fd, client_fd, err;
    struct sockaddr_in server, client;
    char buf[BUFFER_SIZE];

    inet_aton("127.0.0.1", &server.sin_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
        on_error("Could not create socket\n");

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    int opt_val = 1;

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val);

    err = bind(server_fd, (struct sockaddr *)&server, sizeof(server));

    if (err < 0)
        on_error("Could not bind socket\n");

    err = listen(server_fd, 128);

    if (err < 0)
        on_error("Could not listen on socket\n");

    printf("Server is listening on %d\n", port);

    while (1)
    {
        socklen_t client_len = sizeof(client);
        client_fd = accept(server_fd, (struct sockaddr *)&client, &client_len);

        if (client_fd < 0)
            on_error("Could not establish new connection\n");

        while (1)
        {
            int read = recv(client_fd, buf, BUFFER_SIZE, 0);

            if (!read)
                break;

            if (read < 0)
                on_error("Client read failed\n");

            if (strncmp(buf, "OFF", 3) == 0)
                exit(1);

            qsort(buf, (size_t)strlen(buf), (size_t)sizeof(char), cmpfunc);
            printf("%s\n", buf);

            err = send(client_fd, buf, read, 0);
            if (err < 0)
                on_error("Client write failed\n");
        }
    }

    return 0;
}
