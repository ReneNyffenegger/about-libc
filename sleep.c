#include <stdio.h>
#include <unistd.h>

int main () {
  for (int i=5;i>=0; i--) {
    printf("Sleeping for %d seconds\n", i);
    sleep(i);
  }
}
