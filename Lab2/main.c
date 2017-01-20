#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  int ctop[2], ptoc[2];

  pid_t childpid;
  pipe(ctop);
  pipe(ptoc);

  if ((childpid = fork()) == -1) {
    perror("Fork error");
    exit(1);
  }

  if (childpid == 0) { // Child process
    close(ctop[0]);    // Close read pipe
    close(ptoc[1]);    // Close write pipe
    char input[256] = {
	0,
    };
    char readbuffer[256] = {
	0,
    };

    while (strstr(input, "-1") == 0) {
      scanf("%s", input);
      write(ctop[1], input, strlen(input) + 1);
    }

    read(ptoc[0], readbuffer, sizeof(readbuffer));
    printf("\nSum: %s\r\n", readbuffer);
  } else {	  // Parent process
    close(ctop[1]); // Close write pipe
    close(ptoc[0]); // Close read pipe
    char readbuffer[256] = {
	0,
    };
    char writebuffer[256] = {
	0,
    };
    char *endStr;
    int   nums[256] = {
	0,
    };
    int		 sum    = 0;
    unsigned int sumPos = 0;
    read(ctop[0], readbuffer, sizeof(readbuffer));

    while (strcmp(readbuffer, "-1") != 0) {
      nums[sumPos++] = strtol(readbuffer, &endStr, 10);
      read(ctop[0], readbuffer, sizeof(readbuffer));
    }

    for (int C = 0; C < sumPos; C++) { sum += nums[C]; }

    sprintf(writebuffer, "%i", sum);
    write(ptoc[1], writebuffer, sizeof(writebuffer));
  }

  return 0;
}
