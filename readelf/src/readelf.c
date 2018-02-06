#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "readelf.h"

void *load_header(int fd, off_t size)
{
  void *ptr = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);

  return ptr == MAP_FAILED ? NULL : ptr;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "simple-readelf requires exactly 1 argument, %d provided\n%s",
            argc - 1, "Usage: simple-readelf BINARY\n");
    return 1;
  }

  printf("Binary path: %s\n", argv[1]);

  int fd = open(argv[1], O_RDONLY);
  if (fd == -1)
  {
    fprintf(stderr, "simple-readelf: error: impossible to open %s\n", argv[1]);
    return 2;
  }

  struct stat buf;
  if (fstat(fd, &buf) == -1)
    return 3;

  ElfW(Ehdr) *header = load_header(fd, buf.st_size);

  munmap(header, buf.st_size);

  return 0;
}
