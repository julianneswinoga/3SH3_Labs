#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
	int ctop[2], ptoc[2], status;

	pid_t childpid;
	pipe(ctop);
	pipe(ptoc);

	if ((childpid = fork()) == -1) {
		perror("Fork error");
		exit(1);
	}

	if (childpid == 0) { // Child process
		close(ctop[0]);  // Close read pipe
		close(ptoc[1]);  // Close write pipe
		char input[256] = {
			0,
		};
		char readbuffer[256] = {
			0,
		};

		while (strstr(input, "-1") == 0) {
			printf("Enter an unsigned 8 bit integer: ");
			scanf("%s", input);
			write(ctop[1], input, strlen(input) + 1);
		}

		read(ptoc[0], readbuffer, sizeof(readbuffer));
		printf("\nSum: %s\n", readbuffer); // Child printing out sum
	} else {							   // Parent process
		close(ctop[1]);					   // Close write pipe
		close(ptoc[0]);					   // Close read pipe
		char readbuffer[256] = {
			0,
		};
		char writebuffer[256] = {
			0,
		};
		char *  endStr;
		uint8_t nums[256] = {
			0,
		};
		uint16_t	 sum	= 0;
		unsigned int sumPos = 0;
		read(ctop[0], readbuffer, sizeof(readbuffer));

		while (strcmp(readbuffer, "-1") != 0) {
			nums[sumPos++] = (uint8_t)strtol(readbuffer, &endStr, 10);
			read(ctop[0], readbuffer, sizeof(readbuffer));
		}

		for (unsigned int C = 0; C < sumPos; C++) { sum += nums[C]; }

		sprintf(writebuffer, "%i", sum); // Passing sum from parent to child
		write(ptoc[1], writebuffer, sizeof(writebuffer));
		wait(&status); // Wait for child process to die
	}

	return 0;
}
