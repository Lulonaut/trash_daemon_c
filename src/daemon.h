#ifndef DAEMON_H
#define DAEMON_H

int start_daemon(int force);

void daemon_signal_handler(int sig);

#endif //DAEMON_H
