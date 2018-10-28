#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int gen_rand() {
  int fd = open("/dev/urandom", O_RDONLY);
  int randint;
  read(fd, &randint, sizeof(int));
  if (errno) {
    printf("errno: %d Message: %s\n", errno, strerror(errno));
  }
  close(fd);
  return randint;
}

int main() {
  
  int intarray[10];
  
  printf("Generating random numbers:\n");
  for (int i = 0; i < 10; i++) {
    intarray[i] = gen_rand();
    printf("\trandom %d: %d\n", i, intarray[i]);
  }

  printf("\nWriting numbers to a file...\n");
  int wfd = open("randint.txt", O_CREAT | O_WRONLY, 0666);
  write(wfd, intarray, sizeof(int) * 10);
  close(wfd);

  printf("\nReading numbers to a file...\n");
  int newarray[10];
  int rfd = open("randint.txt", O_RDONLY, 0666);
  read(rfd, &newarray, sizeof(int) * 10);
  close(rfd);
  
  printf("\nVerification that written values were the same:\n");
  for (int i = 0; i < 10; i++) {
    printf("\trandom %d: %d\n", i, newarray[i]);
  }

  return 0;
}
