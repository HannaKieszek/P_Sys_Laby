#ifndef SHARED_H
#define SHARED_H

#include <pthread.h>

typedef struct {
    char buf[100];
    int data_ready;
    int exit_flag;

    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Shared;

#endif
