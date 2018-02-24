#include <stdio.h>
// #include <unistd.h>

#include <time.h>


int main () {
  const long nano__s =    1          ; /* One nanosecond  */
  const long micro_s = 1000 * nano__s; /* One microsocond */
  const long milli_s = 1000 * micro_s; /* One millisecond */

  for (int ms = 1000; ms >= 0; ms -= 50) {

    struct timespec duration;
    duration.tv_sec  = 0;
    duration.tv_nsec = milli_s * ms;

    printf("Sleeping for %4d milliseconds\n", ms);
    nanosleep(&duration, NULL);

  }
}
