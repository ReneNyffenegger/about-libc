#include <string.h>
#include <stdio.h>

void tq84_strcmp(char *a, char *b) {

  int   cmp_i = strcmp(a, b);
  char  cmp_c;

  if (cmp_i <  0) cmp_c = '<';
  if (cmp_i == 0) cmp_c = '=';
  if (cmp_i >  0) cmp_c = '>';

  printf("%s %c %s\n", a, cmp_c, b);

}

int main() {

  tq84_strcmp("baz", "foo");
  tq84_strcmp("baz", "bar");
  tq84_strcmp("baz", "baz");
  tq84_strcmp("baz", "FOO");
  tq84_strcmp("baz", "BAR");
  tq84_strcmp("baz", "BAZ");

}
