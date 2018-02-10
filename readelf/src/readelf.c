#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "xlat.h"
#include "readelf.h"

#include "e_type.h"
#include "e_machine.h"
#include "e_version.h"

#include "sh_type.h"

int is_elf(unsigned char *ident)
{
  return ident[0] == 0x7f && ident[1] == 'E' && ident[2] == 'L'
    && ident[3] == 'F';
}

void dump_header(ElfW(Ehdr) *header)
{
  printf("{");
  dump_macro(header, e_type, "\"%s\",");
  dump_macro(header, e_machine, "\"%s\",");
  dump_macro(header, e_version, "\"%s\",");
  dump_entry(header, e_entry, "%lu,");
  dump_entry(header, e_phoff, "%lu,");
  dump_entry(header, e_shoff, "%lu,");
  dump_entry(header, e_flags, "%lu,");
  dump_entry(header, e_ehsize, "%lu,");
  dump_entry(header, e_phentsize, "%lu,");
  dump_entry(header, e_phnum, "%lu,");
  dump_entry(header, e_shentsize, "%lu,");
  dump_entry(header, e_shnum, "%lu,");
  dump_entry(header, e_shstrndx, "%lu");
  printf("}");
}

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

  int ret = is_elf(header->e_ident);
  if (!ret)
    return 4;

  dump_header(header);

  munmap(header, buf.st_size);
  close(fd);

  return 0;
}
