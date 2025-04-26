#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "echo.h"

int main(int argc, char *argv[]) {
    int port, verbose;
    parse_args(argc, argv, &port, &verbose);

    int server_fd = setup_server_socket(port);
    printf("Server listening on port %d\n", port);

    // Accepts and handles clients in a loop
    while (1) {
        int client_fd = accept_client(server_fd);
        int *fd_ptr   = malloc(sizeof(int));
        if (fd_ptr == NULL) {
            perror("malloc");
            close(client_fd);
            continue;
        }
        *fd_ptr = client_fd;

        // Create a new thread for each client
        pthread_t tid;
        if (pthread_create(&tid, NULL, client_thread, fd_ptr) != 0) {
            perror("pthread_create failed");
            free(fd_ptr);
            close(client_fd);
            continue;
        }
        pthread_detach(tid);
    }

    close(server_fd);
    return 0;
}
