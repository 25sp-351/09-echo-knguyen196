#ifndef ECHO_H
#define ECHO_H

void parse_args(int argc, char *argv[], int *port, int *verbose);
int setup_server_socket(int port);
int accept_client(int server_fd);
void handle_client(int client_fd, int verbose);
void *client_thread(void *arg);
#endif
