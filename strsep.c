#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int   main() {

  char *val_1, *val_2, *val_3;

  char* values;
  void* orig;   // keep original malloced region for later freeing it.

  values= malloc(100);
  orig  = values;
  strcpy(values, "foo:bar:baz\n");

  val_1 = strsep(&values, ":" ); printf("values=%s", values);
  val_2 = strsep(&values, ":" ); printf("values=%s", values);
  val_3 = strsep(&values, "\n");

  printf("val_1: %s\n", val_1);
  printf("val_2: %s\n", val_2);
  printf("val_3: %s\n", val_3);

  free(orig);
}
