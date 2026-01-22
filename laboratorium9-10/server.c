#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "server.h"

void start_server(Shared* s) {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    char buf[100];
    ssize_t n;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Serwer działa na porcie 1234\n");

    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        n = read(client_fd, buf, sizeof(buf));
        if (n <= 0) {
            perror("read");
            break;
        }
	buf[strcspn(buf, "\r\n")] = 0;

        pthread_mutex_lock(&s->mutex);
        strcpy(s->buf, buf);
        s->data_ready = 1;
        pthread_cond_signal(&s->cond);
        pthread_mutex_unlock(&s->mutex);

        pthread_mutex_lock(&s->mutex);
        while (s->data_ready)
            pthread_cond_wait(&s->cond, &s->mutex);

        strcpy(buf, s->buf);
        pthread_mutex_unlock(&s->mutex);

        n = write(client_fd, buf, strlen(buf));
        if (n < 0) {
            perror("write");
            break;
        }

	n = write(client_fd, "\n", 1);
	if (n < 0){
	    perror("write");
	    break;
	}
        if (strcmp(buf, "exit") == 0)
            break;
    }

    close(client_fd);
    close(server_fd);
}
