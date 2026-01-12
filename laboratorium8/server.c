#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include "server.h"

void server(char *shm_ptr, sem_t *sem_server, sem_t *sem_worker) {
	while(1) {

		printf("in: ");
		scanf("%99s", shm_ptr);
		sem_post(sem_worker);


		if(strcmp(shm_ptr, "exit") == 0)
		{
			break;
		}

		sem_wait(sem_server);
		printf("out: %s\n", shm_ptr);
	}
}
