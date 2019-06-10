#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_alarm(int signum) {
   printf("SIGALRM received\n");
}

int main() {

   signal(SIGALRM, sig_alarm);

   printf("Setting alarm to go off in 3 seconds\n");
   alarm(3);

   printf("Freeze (pause) current process until a signal is delivered\n");
   pause();

   printf("Signal was delivered - pause is over\n");
}
