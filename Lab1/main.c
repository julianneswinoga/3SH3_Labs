#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void signalHandler(int signo) {
  if (signo == SIGALRM) {
    printf("Alarm\n");
    alarm(2); // Set up the next alarm
    return;
  }

  if (signo == SIGINT) {
    printf("\rCTRL+C pressed!\n");
    return;
  }

  if (signo == SIGTSTP) {
    printf("\rCTRL+Z pressed!\n");
    exit(0);
  }
}

int main(void) {
  if (signal(SIGALRM, signalHandler) == SIG_ERR ||
      signal(SIGINT, signalHandler) == SIG_ERR ||
      signal(SIGTSTP, signalHandler) ==
	  SIG_ERR) { //  register  the  signal  handler
    printf("Failed to register a signal handler");
    exit(1);
  }

  alarm(2); // Fire off the initial alarm

  while (1) sleep(10); // Wait for a signal
}
