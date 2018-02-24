// gcc execvp.c -o execvp

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

   printf("New instance of execvp executed.\n");
   for (int i=0; i<argc; i++) {
     printf("  argv[%d] = %s\n", i, argv[i]);
   }

   if (argc == 1) {
     printf("  argc == 1, exiting without calling fork and execve\n");
     exit(0);
   }

   if (fork()) {
//   Parent.
     exit(0);
   }

// Child.

// Reduce arguments by one element
   argv[argc] = NULL; 

   argv[0] = "What is this used for?";
   execvp("./execvp", argv);
   printf("Normaly, not reached\n");

}
