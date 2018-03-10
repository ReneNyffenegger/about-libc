// #define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>

int main() {
 //
 // Write some text to STDOUT (1). The lenght of the
 // text is 12 (last paramter).
 //
    syscall(SYS_write, 1, "Hello World\n", 12);
}
