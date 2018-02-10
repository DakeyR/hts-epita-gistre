#include <elf.h>
#include <link.h>

#define dump_entry(Ptr, Field, Format) \
  printf("\"" #Field "\":" Format, (Ptr)->Field)

#define dump_macro(Ptr, Field, Format) \
  printf("\"" #Field "\":" Format, xlookup(Field, (Ptr)->Field))

#define dump_macro_dflt(val, Field, Format) \
  printf("\"" #Field "\":" Format, val)

int is_elf(unsigned char *ident);
void dump_header(ElfW(Ehdr) *header);
void *get_strtab(ElfW(Ehdr) *header);
void dump_shdrs(ElfW(Shdr) *shdrs, unsigned int shnum, char *strtab,
                             ElfW(Shdr) **dynsym, ElfW(Shdr) **symtab);
void dump_phdrs(ElfW(Phdr) *phdrs, unsigned int phnum);
void dump_section_header(ElfW(Shdr) *shead, char *strtab);
void dump_program_header(ElfW(Phdr) *phead);
void dump_symbols(ElfW(Shdr) *shead, ElfW(Ehdr) *header, char *strtab);
void *load_header(int fd, off_t size);
void *retrieve_header();
