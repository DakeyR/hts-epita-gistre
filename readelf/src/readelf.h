#include <elf.h>
#include <link.h>

#define dump_entry(Ptr, Field, Format) \
  printf("\"" #Field "\":" Format, (Ptr)->Field)

#define dump_macro(Ptr, Field, Format) \
  printf("\"" #Field "\":" Format, xlookup(Field, (Ptr)->Field))

int is_elf(unsigned char *ident);
void dump_header(ElfW(Ehdr) *header);
void *get_strtab(ElfW(Ehdr) *header);
void dump_shdrs(ElfW(Shdr) *shdrs, unsigned int shnum);
void dump_section_header(ElfW(Shdr) *shead);
void *load_header(int fd, off_t size);
void *retrieve_header();
