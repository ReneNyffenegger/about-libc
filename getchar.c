#include <stdio.h>
#include <stdlib.h>

int main() {

    printf("Press any key to continue.\n");

 //
 // getchar can be used to wait for a user to press any key.
 // Note: getchar returns an int, not a char. The returned
 // value is EOF when an error occurs.
 //
 // Apparently, getchar() still needs the enter key to be pressed.
 // Compare https://stackoverflow.com/q/1798511/180275
 //
    int res = getchar();

    if (res == EOF) {
      perror("Error reading the character");
      exit (1);
    }

    unsigned char characterPressed = (unsigned char) res;
    
    printf("Continuing. You pressed %c\n", characterPressed);
}
