//
// Created by lulonaut on 10/18/24.
//


#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "client.h"

#define BUFSIZE 1024
#define SOCK_PATH "/home/lulonaut/trashsocket"


int connect_to_server() {
    const int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        fputs("Failed to create socket", stderr);
        return 1;
    }

    struct sockaddr_un sock_addr = {0};
    sock_addr.sun_family = AF_UNIX;
    strncpy(sock_addr.sun_path, SOCK_PATH, sizeof(sock_addr.sun_path) - 1);


    if (connect(socket_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0) {
        fputs("Failed to connect to socket", stderr);
    }

    char buffer[BUFSIZE] = {0};
    strcat(buffer, "Testmessage\0");
    if (send(socket_fd, buffer, BUFSIZE, 0) < 0) {
        fputs("Failed to send data", stderr);
    }
    close(socket_fd);
    return 0;
}
