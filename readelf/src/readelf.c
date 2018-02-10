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

#include "p_type.h"

#include "st_shndx.h"

int is_elf(unsigned char *ident)
{
  return ident[0] == 0x7f && ident[1] == 'E' && ident[2] == 'L'
    && ident[3] == 'F';
}

void dump_header(ElfW(Ehdr) *header)
{
  printf("\"header\":{");
  dump_macro(header, e_type, "\"%s\",");
  dump_macro(header, e_machine, "\"%s\",");
  dump_macro(header, e_version, "\"%s\",");
  dump_entry(header, e_entry, "%lu,");
  dump_entry(header, e_phoff, "%lu,");
  dump_entry(header, e_shoff, "%lu,");
  dump_entry(header, e_flags, "%u,");
  dump_entry(header, e_ehsize, "%d,");
  dump_entry(header, e_phentsize, "%d,");
  dump_entry(header, e_phnum, "%d,");
  dump_entry(header, e_shentsize, "%d,");
  dump_entry(header, e_shnum, "%u,");
  dump_entry(header, e_shstrndx, "%d");
  printf("}\n");
}

void *get_strtab(ElfW(Ehdr) *header)
{
  ElfW(Shdr) *shdr =  (void *)((char *)header + header->e_shoff);
  shdr = shdr + header->e_shstrndx;
  return (char *)header + shdr->sh_offset;
}

void dump_shdrs(ElfW(Shdr) *shdrs, unsigned int shnum, char *strtab,
                             ElfW(Shdr) **dynsym, ElfW(Shdr) **symtab)
{
  printf("\"sections\":[");
  for (ElfW(Half) i = 0; i < shnum - 1; i++)
  {
    if ((shdrs + i)->sh_type == SHT_DYNSYM)
      *dynsym = (shdrs + i);
    else if ((shdrs + i)->sh_type == SHT_SYMTAB)
      *symtab = (shdrs + i);

    dump_section_header(shdrs + i, strtab);
    printf(",");
  }
  dump_section_header(shdrs + (shnum - 1), strtab);
  printf("]\n");
}

void dump_phdrs(ElfW(Phdr) *phdrs, unsigned int phnum)
{
  printf("\"segments\":[");
  for (ElfW(Half) i = 0; i < phnum - 1; i++)
  {
    dump_program_header(phdrs + i);
    printf(",");
  }
  dump_program_header(phdrs + (phnum - 1));
  printf("]\n");
}

void dump_section_header(ElfW(Shdr) *shead, char *strtab)
{
  printf("{");
  dump_entry(shead, sh_name, "%u,");
  dump_macro(shead, sh_type, "\"%s\",");
  dump_entry(shead, sh_flags, "%lu,");
  dump_entry(shead, sh_addr, "%lu,");
  dump_entry(shead, sh_offset, "%lu,");
  dump_entry(shead, sh_size, "%lu,");
  dump_entry(shead, sh_link, "%d,");
  dump_entry(shead, sh_info, "%d,");
  dump_entry(shead, sh_addralign, "%lu,");
  dump_entry(shead, sh_entsize, "%lu,");
  printf("\"name\":\"%s\"", strtab + shead->sh_name);
  printf("}\n");
}

void dump_program_header(ElfW(Phdr) *phead)
{
  printf("{");
  dump_macro(phead, p_type, "\"%s\",");
  dump_entry(phead, p_offset, "%lu,");
  dump_entry(phead, p_vaddr, "%lu,");
  dump_entry(phead, p_paddr, "%lu,");
  dump_entry(phead, p_filesz, "%lu,");
  dump_entry(phead, p_memsz, "%lu,");
  dump_entry(phead, p_flags, "%u,");
  dump_entry(phead, p_align, "%lu");
  printf("}\n");
}

void dump_symbols(ElfW(Shdr) *shead, ElfW(Ehdr) *header, char *strtab)
{
  ElfW(Shdr) *tmp = (void *)((char *)header + header->e_shoff);
  char *local_strtab = (char *)header + tmp[shead->sh_link].sh_offset;

  printf("{\"name\":\"%s\",", strtab + shead->sh_name);
  printf("\"data\":[\n");
  ElfW(Xword) size = shead->sh_size;
  size = size / sizeof (ElfW(Sym));


  ElfW(Sym) *symtab = (void *)((char *)header + shead->sh_offset);

  for (ElfW(Xword) i = 0; i < size - 1; i++)
  {
    ElfW(Sym) *tmp = symtab + i;
    printf("{");
    dump_entry(tmp, st_name, "%u,");
    const char *str = xlookup(st_shndx, tmp->st_shndx);
    if (str)
      dump_macro_dflt(str, st_shndx, "\"%s\",");
    else
      dump_macro_dflt(tmp->st_shndx, st_shndx, "%u,");
    dump_entry(tmp, st_value, "%lu,");
    dump_entry(tmp, st_size, "%lu,");
    printf("\"name\": \"%s\"", local_strtab + tmp->st_name);
    printf("},\n");
  }

  symtab = symtab + (size - 1);

  printf("{");
  dump_entry(symtab, st_name, "%u,");
  const char *str = xlookup(st_shndx, symtab->st_shndx);
  if (str)
    dump_macro_dflt(str, st_shndx, "\"%s\",");
  else
    dump_macro_dflt(symtab->st_shndx, st_shndx, "%u,");
  dump_entry(symtab, st_value, "%lu,");
  dump_entry(symtab, st_size, "%lu,");
  printf("\"name\": \"%s\"", local_strtab + symtab->st_name);
  printf("}\n");
  printf("]}");
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

  char *strtab = get_strtab(header);

  printf("{\n");

  dump_header(header);
  printf(",");

  ElfW(Shdr) *dynsym = NULL;
  ElfW(Shdr) *symtab = NULL;

  dump_shdrs((void *)((char *)header + header->e_shoff),
               header->e_shnum, strtab, &dynsym, &symtab);
  printf(",");

  dump_phdrs((void *)((char *)header + header->e_phoff), header->e_phnum);
  printf(",");

  printf("\"symbols\":[");
  if (dynsym)
  {
    dump_symbols(dynsym, header, strtab);
    if (symtab)
      printf(",");
  }
  if (symtab) {
    dump_symbols(symtab, header, strtab);
  }
  printf("]");

  printf("}");

  munmap(header, buf.st_size);
  close(fd);

  return 0;
}
