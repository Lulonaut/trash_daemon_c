#include <signal.h>
#include <stdio.h>
#include <string.h>

#include "daemon.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--daemon") == 0) {
            int force = 0;
            if (argc > 2 && strcmp(argv[2], "--force") == 0) {
                force = 1;
            }

            signal(2, daemon_signal_handler); // SIGINT
            signal(15, daemon_signal_handler); // SIGTERM

            return start_daemon(force);
        } else {
            puts("Client not yet implemented");
        }
    }

    return 0;
}
