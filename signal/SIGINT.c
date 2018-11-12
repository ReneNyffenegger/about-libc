#include <signal.h>
#include <stdio.h>
#include <time.h>

void ctrl_c_pressed(int signum) {
 //
 // The user pressed ctrl-c. The for-loop
 // below stoped, the following message is printed
 // and the loop is resumed again.
 //
    printf("ctrl-c was pressed.\n");
}

int main() {

    struct timespec duration;
    duration.tv_sec  = 0;
    duration.tv_nsec = 1e6 * 100; // 100 milli Seconds

 //
 // Call ctrl_c_pressed when the user presses
 // ctrl-c:
 //
    signal(SIGINT, ctrl_c_pressed);

 //
 // Print the number 0 through 19 in intervals
 // of 100 milliseconds:
 //
    for (int i = 0; i<20; i++) {
        printf("i = %d\n", i);
        nanosleep(&duration, NULL);
    }

}
