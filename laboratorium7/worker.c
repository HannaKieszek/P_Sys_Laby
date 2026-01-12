#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "worker.h"

void worker(int fdread, int fdwrite)
{
	char text2[20];

        while(1)
	{
		read(fdread, text2, 20);
		if (strcmp(text2, "exit") == 0)
		{
			break;
		}
		text2[0]='X';
		write(fdwrite, text2, strlen(text2)+1);
	}
}
