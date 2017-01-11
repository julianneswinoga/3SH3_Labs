#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>

int main(void) {
	pid_t childpid;

	if ((childpid = fork()) == -1) {
		perror("Fork error");
		exit(1);
	}

	if (childpid == 0) { // Child process
		int pageSize;
		pageSize = getpagesize();
		printf("Page size: %i", pageSize);

	} else { // Parent process
	}

	return 0;
}
