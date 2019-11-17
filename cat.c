#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

void cat(char *fname) {
  int fd = open(fname, O_RDONLY);
  struct stat st;
  fstat(fd, &st);
  int fsize = st.st_size;

  char *map = mmap(0, fsize, PROT_READ, MAP_PRIVATE, fd, 0);

  write(1, map, fsize);

  munmap(map, fsize);
  close(fd);
}

int main(int argc, char *argv[]){
  if(argc != 2)  exit(EXIT_FAILURE);

  cat(argv[1]);

  exit(EXIT_SUCCESS);
}
