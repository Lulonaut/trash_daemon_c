#include "daemon.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define BUFSIZE 1024
#define SOCK_PATH "/home/lulonaut/trashsocket"

void socket_loop(const int socket_fd) {
    char buf[BUFSIZE];
    while (1) {
        puts("Waiting for connection...");

        const int socket_connection = accept(socket_fd, NULL, NULL);
        const int bytes_read = read(socket_connection, buf, BUFSIZE);
        buf[bytes_read] = '\0';

        printf("Received %d bytes\n", bytes_read);
        if (bytes_read <= 0) {
            fputs("Received no useful data, closing connection", stderr);
            close(socket_connection);
            continue;
        }

        if (strncmp(buf, "exit", 4) == 0) {
            puts("Exiting");
            close(socket_fd);
            break;
        }
        buf[bytes_read] = '\0';
        printf("%s\n", buf);

        close(socket_connection);
    }
}

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

    const int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        fputs("Failed to create socket", stderr);
        return 1;
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
        return 1;
    }

    socket_loop(socket_fd);
    return 0;
}

void daemon_signal_handler(const int sig) {
    printf("Received signal %d, exiting.\n", sig);
    unlink(SOCK_PATH);
    exit(0);
}
