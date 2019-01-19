#include <fcntl.h>

#include <unistd.h> // close()
#include <stdio.h>  // printf()
#include <stdlib.h> // exit()
#include <string.h> // strlen()

int main() {

    int flags =
        O_WRONLY| // O_RDONLY, O_RDWR
        O_CREAT | // O_EXCL, O_TMPFILE, O_NONBLOCK, O_NOCTTY, O_TRUNC
        0       ; // O_APPEND, O_NONBLOCK, O_NOATIME

    mode_t mode =
        S_IRUSR | // user read
        S_IWUSR ; // user write

    int file_descriptor = open("out-file", flags, mode);
    if (file_descriptor < 0) {
      printf("Could not open file\n");
      exit(1);
    }

    char*  text = "foo\nbar\nbaz\n";
    size_t size = strlen(text);

 //
 // GNU's manual says:
 //     The return value is the number of bytes actually written. This may be
 //     size, but can always be smaller. Your program should always call write
 //     in a loop, iterating until all the data is written.
    int written = write(file_descriptor, text, size);

    close(file_descriptor);
}
