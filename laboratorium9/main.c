#include "server.h"
#include "worker.h"
#include <pthread.h>
#include "shared.h"

int main() {
    pthread_t worker;
    Shared shared = {
        .data_ready = 0,
        .exit_flag = 0,
        .mutex = PTHREAD_MUTEX_INITIALIZER,
        .cond = PTHREAD_COND_INITIALIZER
    };

    pthread_create(&worker, NULL, worker_thread, &shared);
    start_server(&shared);
    pthread_join(worker, NULL);

    return 0;
}
