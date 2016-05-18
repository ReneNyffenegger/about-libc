//
//  Some calls:
//    ./getopt
//    ./getopt -h
//    ./getopt -rhello foo
//    ./getopt -rhello -o
//    ./getopt -rhello -oworld
//    ./getopt -rhello -o foo bar baz
//
//
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Needed for getopt

void usage() {

  printf("\n\n getopt [-h] [-r R] [-o [O] ]\n\n");
  exit (0);

}

int main (int argc, char **argv) {

  char *R = NULL;
  int   o = 0;
  char *O = "default O value";
  int index;
  int opt;

  opterr = 0;

  while ((opt = getopt (argc, argv, 
            "h"       // no colon:   just a flag
            "r:"      // one colon:  required value
            "o::"     // two colons: optional value
          )) != -1) { // -1: No more options present, terminate loop

    switch (opt) {

      case 'h':
        usage();

      case 'r':
        R = optarg;
        break;

      case 'o':
        O = optarg;
        o = 1;
        break;

      case '?': // ? indicates an error
                // optopt now contains the option that caused
                // the error

        if (optopt == 'r') {
          fprintf (stderr, "-r without value.\n");
        }
        else if (isprint (optopt)) {
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        }
        else {
          fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
        }

        return 1;
        
      default:
        abort ();
      }
  }

  printf ("R = %s, O = %s, o = %d\n", R, O, o);

  for (index = optind; index < argc; index++) {
    printf ("Non-option argument %s\n", argv[index]);
  }

  return 0;
}

