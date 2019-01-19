#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>      // printf()
#include <stdlib.h>     // exit()


int main() {

    int fd = open("words.txt", O_RDONLY);
    if (fd < 0) exit(1);

    char word[4];

    off_t new_pos = lseek(fd, 4, SEEK_SET);
    read(fd, word, 3);
    word[4] = 0;

    printf("Word @ pos %d: %s\n", new_pos, word);

    new_pos = lseek(fd, 1, SEEK_CUR); // Skip new line characters

    read(fd, word, 3);
    printf("Word @ pos %d: %s\n", new_pos, word);

    close(fd);

}
