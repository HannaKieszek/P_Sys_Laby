#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include "worker.h"

void worker(char *shm_ptr, sem_t *sem_server, sem_t *sem_worker) {
	while(1) {
		sem_wait(sem_worker);

		if (strcmp(shm_ptr, "exit") == 0)
		{
			sem_post(sem_server);
			break;
		}
		shm_ptr[0]='X';

		sem_post(sem_server);
	}
}
