#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t p = fork();
  if (p < 0) {
    printf("Error while forking\n");
  }
  else if (p == 0) {
    printf("I am the child, my pid is %d, the parent's pid is %d\n", getpid(), getppid());
  }
  else {
    printf("I am the parent of child process %d, my pid is %d\n", p, getpid());
  }
}
