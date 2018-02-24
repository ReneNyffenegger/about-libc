#include <stdio.h>
#include <stdlib.h>

void clean_up() {
  printf("Entered clean_up.\n");
  printf("Called when main terminates or exit() is called.\n");
  printf("Not called, for example, when process terminated with ctrl-c.\n");
}

int main() {

  atexit(clean_up);

  unsigned int i=0;
  
  while (i<5000) {
    printf("  %9d\n", i++);
  }

}
