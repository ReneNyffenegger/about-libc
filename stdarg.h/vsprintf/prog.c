#include <stdarg.h>
#include <stdio.h>
#include <time.h>


void printfWithTimestamp(char* fmt, ...) {
  va_list args;

  char buf[256]; // 256 bytes should be enough for anyone...

  va_start(args, fmt);
  vsprintf(buf, fmt, args);
  va_end(args);

  time_t t      = time(NULL);;
  struct tm *tm = localtime(&t);

  printf("%4d-%02d-%02d %02d:%02d:%02d | ", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

  printf(buf);
  printf("\n");
}


int main() {

  printfWithTimestamp("The number is %d, the text is %s.", 42, "Hello world");
  sleep(3);
  printfWithTimestamp("Three seconds later.");

}
