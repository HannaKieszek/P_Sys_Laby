#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "server.h"

void server(int fdwrite, int fdread)
{

	char text[20];
	char text_m[20];

	while(1)
	{
		printf("in: ");
                scanf("%s", text);
                write(fdwrite, text, strlen(text)+1);
                if (strcmp(text, "exit") == 0)
                {
	                wait(NULL);
                        break;
                }

		read(fdread, text_m, 20);
                printf("out: %s\n", text_m);
	}
}
