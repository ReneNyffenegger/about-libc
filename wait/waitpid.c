#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void child() {

  for (int i=0; i<5; i++) {
    sleep(1);
    printf("%d\n", i);
  }
  exit(0);

}
void parent(pid_t pid_child) {
  int status;

  waitpid(pid_child, &status, 0);
  printf("child exited, status = %d\n", status);

}

int main() {

  pid_t pid = fork();

  if      (pid == 0) child ();
  else if (pid  > 0) parent(pid);
  else     printf("fork failed\n");

}
