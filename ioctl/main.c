#include <sys/ioctl.h>

#include <stdio.h>
#include <stdlib.h>     // exit()
#include <fcntl.h>      // open()
#include <linux/fs.h>   // BLKSSZGET

int main() {

   int fd = open("/dev/sda", O_RDWR);
   if (fd == -1) exit(1);

   int sectorSize;
   if (ioctl(fd, BLKSSZGET, &sectorSize)) exit(2);

   printf("Sector size: %d\n", sectorSize);
}
