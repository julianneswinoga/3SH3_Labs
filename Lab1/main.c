#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// user -defined  signal  handler  for  alarm.
void  alarm_handler(int  signo) {
	if (signo  ==  SIGALRM)
		printf (" alarm  goes  off\n");
}

int  main(void) {
	if (signal(SIGALRM, alarm_handler) ==  SIG_ERR) { //  register  the  signal  handler
		printf (" failed  to  register  alarm  handler .");
		exit (1);
	}

	alarm (3);                 // set  alarm  to fire in 3 seconds.

	while (1)
		sleep (10); // wait  until  alarm  goes  off
}
