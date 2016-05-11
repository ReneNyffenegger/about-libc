#include <stdio.h>

int main() {

  printf("Type character: ");

  // Note: needs Enter pressed
  char c = getc(stdin);

  printf("c = %c\n", c);
}
