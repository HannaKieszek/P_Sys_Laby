#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "server.h"
#include "worker.h"

int main(int argc, char *argv[])
{
	char * server2worker = "/tmp/server2worker";
	char * worker2server = "/tmp/worker2server";

	if(argc != 2)
	{
		fprintf(stderr, "Niewalasciwa liczba argumentow\n");
		return 1;
	}

        if(strcmp(argv[1], "server") == 0)
        {

		mkfifo(worker2server, 0666);
		mkfifo(server2worker, 0666);

		int fdwrite = open(server2worker, O_WRONLY);
		int fdread = open(worker2server, O_RDONLY);

		server(fdwrite, fdread);

		close(fdread);
		close(fdwrite);

		unlink(worker2server);
		unlink(server2worker);

	}
	else if(strcmp(argv[1], "worker") ==0)
	{
                int fdread = open(server2worker, O_RDONLY);
		int fdwrite = open(worker2server, O_WRONLY);

		worker(fdread, fdwrite);

                close(fdread);
                close(fdwrite);

	}
	else
	{
		fprintf(stderr, "Nieznany argument: %s\n", argv[1]);
		return 1;
	}


	return 0;
}
