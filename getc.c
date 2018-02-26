#include <stdio.h>

int main() {

  printf("Type character: ");

  // Note: needs Enter pressed. Compare with getchar().
  char c = getc(stdin);

  printf("c = %c\n", c);
}
