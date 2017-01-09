# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
int main (void) {
	int fd [2], nbytes;
	pid_t childpid;
	pipe (fd);

	if ((childpid = fork()) == -1) {
		perror ("Fork error");
		exit (1);
	}

	if (childpid == 0) {
		close (fd[0]);
		char string[256];
		int stringPos = 0;

		while (strstr(string, "-1") == 0) {
			string[stringPos] = getc(stdin);
			char sendStr[2] = {string[stringPos], 0};
			stringPos++;
			write (fd[1], sendStr, (strlen(sendStr) + 1));
		}

	} else {
		close (fd[1]);
		char readbuffer[80];
		nbytes = read (fd[0], readbuffer, sizeof(readbuffer));
		printf ("Received string: %s", readbuffer);
	}

	return 0;
}
