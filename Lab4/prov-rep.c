#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/mman.h>

#define ALARM_TIME 2

pid_t childpid;

void signalHandler(int  signo) {
	if (signo  ==  SIGALRM && childpid == 0) {
		pageSize = getpagesize();
		printf("Page size: %i\n", pageSize);
		alarm(ALARM_TIME); // Set up the next alarm
	}
}

void main(void) {
	if (signal(SIGALRM, signalHandler) ==  SIG_ERR) { //  register  the  signal  handler
		printf ("Failed to register a signal handler");
		exit (1);
	}

	if ((childpid = fork()) == -1) {
		perror("Fork error");
		exit(1);
	}

	if (childpid == 0) { // Child process
		int pageSize;
		alarm(ALARM_TIME); // Set the initial alarm
		while (1) { sleep(10); }

	} else { // Parent process
		printf("Parent process\n");
		while (1) { sleep(10); }
	}

	exit(0); // Exit all processes
}
