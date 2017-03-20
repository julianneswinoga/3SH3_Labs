#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

#define ALARM_TIME 10

pid_t childpid;
int   pageSize;
char *res;

void signalHandler(int signo) {
	if (signo == SIGALRM && childpid == 0) {
		unsigned char *vec;
		pageSize     = getpagesize();
		int numPages = (pageSize + pageSize - 1) / pageSize;
		vec          = malloc(numPages);

		if (vec == NULL) {
			printf("malloc error\n");
			exit(1);
		}

		if (mincore(res, pageSize, vec) == -1) {
			printf("mincore error\n");
			exit(1);
		}

		for (int i = 0; i < numPages; i++) {
			if (i % 64 == 0)
				printf("%s%10p: ", i == 0 ? "" : "\n", res + (i * pageSize));

			printf("%s", (vec[i] & 0x01) ? "In memory" : "Not in memory");
		}

		printf("\n");
		free(vec); // Free the vector that was allocated
		printf("Page size: %i\n", pageSize);
		alarm(ALARM_TIME); // Set up the next alarm
	}
}

void main(void) {
	if (signal(SIGALRM, signalHandler) ==
	    SIG_ERR) { //  register  the  signal  handler
		printf("Failed to register a signal handler");
		exit(1);
	}

	int resourseFile;
	pageSize     = getpagesize();
	resourseFile = open("res.txt", O_RDWR);

	if (resourseFile == -1) {
		printf("File not found\n");
		exit(1);
	}

	res = mmap((uintptr_t)0, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED,
	           resourseFile, 0);

	if (res == MAP_FAILED) {
		printf("Memory map failed\n");
		exit(1);
	}

	if ((childpid = fork()) == -1) {
		perror("Fork error");
		exit(1);
	}

	if (childpid == 0) { // Child process
		int pageSize;
		alarm(ALARM_TIME); // Set the initial alarm

		while (1) { sleep(10); } // Everything is triggered by the alarm signal

	} else { // Parent process
		while (1) { sleep(10); }
	}

	exit(0); // Exit all processes
}
