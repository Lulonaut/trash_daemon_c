#include <signal.h>
#include <stdio.h>
#include <string.h>

#include "daemon.h"
#include "client.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--daemon") == 0) {
            int force = 0;
            if (argc > 2 && strcmp(argv[2], "--force") == 0) {
                force = 1;
            }

            struct sigaction sa = {0};
            sa.sa_handler = daemon_signal_handler;
            sa.sa_flags = SA_RESTART;

            sigaction(SIGINT, &sa, NULL);
            sigaction(SIGTERM, &sa, NULL);
            // IDE restart
            sigaction(SIGHUP, &sa, NULL);


            return start_daemon(force);
        }
    }

    // Assume client for now
    connect_to_server();

    return 0;
}
