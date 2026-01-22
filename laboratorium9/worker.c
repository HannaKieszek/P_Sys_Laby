#include <string.h>
#include "worker.h"

void* worker_thread(void* arg) {
    Shared* s = (Shared*)arg;
    char local_buf[100];

    while (1) {
        pthread_mutex_lock(&s->mutex);
        while (!s->data_ready)
            pthread_cond_wait(&s->cond, &s->mutex);

        strcpy(local_buf, s->buf);

        if (strcmp(local_buf, "exit") == 0) {
            s->exit_flag = 1;
        } else {
            local_buf[0] = 'X';
            strcpy(s->buf, local_buf);
        }

        s->data_ready = 0;
        pthread_cond_signal(&s->cond);
        pthread_mutex_unlock(&s->mutex);

        if (s->exit_flag)
            break;
    }
    return NULL;
}
