#include <sys/stat.h>
#include <sys/sysmacros.h> // major(), minor()
#include <stdlib.h>        // exit()
#include <time.h>          // ctime()
#include <stdio.h>

void print_rwx(mode_t mode, mode_t bit, char rwx) {
  if (mode & bit) {
    printf("%c", rwx);
  }
  else {
    printf("-");
  }
}

int main(int argc, char* argv[]) {

  char* pathname;

  if (argc == 1) {
    pathname = argv[0];
  }
  else {
    pathname = argv[1];
  }

  printf("pathname = %s, argc=%d\n", pathname, argc);
  struct stat s;

  if (stat(pathname, &s) < 0) {
    printf("Could not stat %s\n", pathname);
    exit(-1);
  }

  printf("major/minor:  %d/%d\n", major(s.st_dev), minor(s.st_dev));
  printf("Inode Nr: %d\n", s.st_ino);

  printf("mode: ");
  print_rwx(s.st_mode, S_IRUSR, 'r'); print_rwx(s.st_mode, S_IWUSR, 'w'); print_rwx(s.st_mode, S_IXUSR, 'x');
  print_rwx(s.st_mode, S_IRGRP, 'r'); print_rwx(s.st_mode, S_IWGRP, 'w'); print_rwx(s.st_mode, S_IXGRP, 'x');
  print_rwx(s.st_mode, S_IROTH, 'r'); print_rwx(s.st_mode, S_IWOTH, 'w'); print_rwx(s.st_mode, S_IXOTH, 'x');
  printf("\n");

  printf("Number of hard links: %d\n", s.st_nlink);
  printf("uid: %ld, gid: %ld\n", s.st_uid, s.st_gid);
  printf("Size: %lld\n", s.st_size);
  printf("ctime: %s", ctime(&s.st_ctime));
  printf("atime: %s", ctime(&s.st_atime));
  printf("mtime: %s", ctime(&s.st_mtime));

}
