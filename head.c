#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

void head(char *fname) {
  int fd = open(fname, O_RDONLY);
  struct stat st;
  fstat(fd, &st);
  int fsize = st.st_size;
  int n_lines = 0;

  char *map = mmap(0, fsize, PROT_READ, MAP_PRIVATE, fd, 0);
  // 末尾のアドレスを cursorに代入する
  char *cursor = map;

  for (int i = 0; i < fsize; i++){
    cursor++;

    if (*cursor == '\n') n_lines++;

    if (n_lines == 10){
      cursor--;
      break;
    }
  }

  write(1, map, cursor-map);

  munmap(map, fsize);
  close(fd);
}

int main(int argc, char *argv[]){
  if(argc != 2)  exit(EXIT_FAILURE);

  head(argv[1]);

  exit(EXIT_SUCCESS);
}
