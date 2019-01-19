#include <stdio.h>

#include <stdlib.h>  // exit()

int main() {

   FILE* f = fopen("a.file", "w");

   if (!f) {
     printf("Could not open file\n");
     exit(1);
   }

   fprintf(f, "foo\nbar\nbaz\n");

   fclose(f);
}
