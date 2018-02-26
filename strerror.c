//
//  See also perror(), sys_errorlist[]
//
#include <string.h>
#include <stdio.h>

int main() {

  for (int i=0; i<sys_nerr; i++) {
    printf("%3d: %s\n", i, strerror(i));
  }

}
