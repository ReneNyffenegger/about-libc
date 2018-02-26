//
//  sys_errlist is deprecated, strerror() should be used.
//
#include <errno.h>
#include <stdio.h>

int main() {

  for (int i=0; i<sys_nerr; i++) {
    printf("%3d: %s\n", i, sys_errlist[i]);
  }

}
