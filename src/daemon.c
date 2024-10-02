#include "daemon.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define BUFSIZE 1024
#define SOCK_PATH "/home/lulonaut/trashsocket"

int start_daemon(const int force) {
    // Check if the socket file already exists
    if (access(SOCK_PATH, F_OK) == 0) {
        puts("Socket file already exists. Is another daemon already running?");

        if (force == 1) {
            puts("--force passed, deleting file and starting the daemon.");
            unlink(SOCK_PATH);
        } else {
            puts("Quitting. Either kill the existing daemon or pass --force to start anyways.");
            return 1;
        }
    }

    fprintf(stderr, "Starting daemon at %s\n", SOCK_PATH);

    int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        fputs("Failed to create socket", stderr);
        exit(1);
    }

    struct sockaddr_un sock_addr = {0};
    sock_addr.sun_family = AF_UNIX;
    strncpy(sock_addr.sun_path, SOCK_PATH, sizeof(sock_addr.sun_path) - 1);
    if (bind(socket_fd, (struct sockaddr *) &sock_addr, sizeof(sock_addr)) < 0) {
        fputs("Failed to bind socket", stderr);
        exit(1);
    }
    if (listen(socket_fd, 5) < 0) {
        fputs("Failed to listen on socket", stderr);
        exit(1);
    }

    int socket_data;
    while (1) {



    }
    // TODO read, client impl, signal handler -> delete socket file

    return 0;
}
