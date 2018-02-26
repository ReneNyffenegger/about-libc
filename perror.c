// #include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {

  int fd = open("/this/file/does/not/exist", O_RDONLY);

  if (fd == -1) {
    // error
    perror("Could not open file, error is");
    exit (1);
  
  }

}
