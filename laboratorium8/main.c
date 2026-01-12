#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include "server.h"
#include "worker.h"

#define SHM_NAME "/shm_lab"
#define SEM_SERVER "/sem_server"
#define SEM_WORKER "/sem_worker"
#define SHM_SIZE 100

int main(int argc, char *argv[]) {
		int shm_fd;
		char *shm_ptr;

		sem_t *sem_server;
		sem_t *sem_worker;

		if (argc != 2)
		{
			fprintf(stderr, "Niewlasciwa liczba argumentow\n");
			return 1;
		}

		if (strcmp(argv[1], "server") == 0)
		{

			shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
			ftruncate(shm_fd, SHM_SIZE);

			shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

			sem_server = sem_open(SEM_SERVER, O_CREAT, 0666, 0);
			sem_worker = sem_open(SEM_WORKER, O_CREAT, 0666, 0);

			server(shm_ptr, sem_server, sem_worker);

			munmap(shm_ptr, SHM_SIZE);
			close(shm_fd);

			sem_close(sem_server);
			sem_close(sem_worker);

			sem_unlink(SEM_SERVER);
			sem_unlink(SEM_WORKER);
			shm_unlink(SHM_NAME);
	}

	else if (strcmp(argv[1], "worker") == 0) {

		shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);

		shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

		sem_server = sem_open(SEM_SERVER, 0);
		sem_worker = sem_open(SEM_WORKER, 0);

		worker(shm_ptr, sem_server, sem_worker);

		munmap(shm_ptr, SHM_SIZE);
		close(shm_fd);

		sem_close(sem_server);
		sem_close(sem_worker);
	}

	return 0;
}
