#include <stdio.h>
#include <stdlib.h>

int main() {

  void* mem_1 = malloc(0xff);
  void* mem_2 = malloc(0xff);
  void* mem_3 = malloc(0xff);

  printf("%llx\n", mem_1);
  printf("%llx\n", mem_2);
  printf("%llx\n", mem_3);

  free(mem_1);
  free(mem_2);
  free(mem_3);

}
