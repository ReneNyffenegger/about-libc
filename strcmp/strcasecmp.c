#include <string.h>
#include <stdio.h>

void tq84_strcasecmp(char *a, char *b) {

  int   cmp_i = strcasecmp(a, b);
  char  cmp_c;

  if (cmp_i <  0) cmp_c = '<';
  if (cmp_i == 0) cmp_c = '=';
  if (cmp_i >  0) cmp_c = '>';

  printf("%s %c %s\n", a, cmp_c, b);

}

int main() {

  tq84_strcasecmp("baz", "foo");
  tq84_strcasecmp("baz", "bar");
  tq84_strcasecmp("baz", "baz");
  tq84_strcasecmp("baz", "FOO");
  tq84_strcasecmp("baz", "BAR");
  tq84_strcasecmp("baz", "BAZ");

}
