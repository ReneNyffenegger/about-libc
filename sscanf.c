#include <stdio.h>

int main() {

  int int_1, int_2, int_3;

  int r = sscanf("42", "%d", &int_1);
  printf("r=%d, a=%d\n", r, int_1);

  r = sscanf("  \t  \n 42 \n\t  1111 222, etc. ect.", "%d %d %d", &int_1, &int_2, &int_3);
  printf("r=%d, int_1=%d, int_2=%d, int_3=%d\n", r, int_1, int_2, int_3);

}
