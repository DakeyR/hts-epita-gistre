#include <elf.h>
#include <link.h>
#include "gnu_hash.h"

int my_strcmp(const char *str1, const char *str2);
int is_absent(struct gnu_hash_table *ght, ElfW(Word) hash);

void *lookup_sym(struct gnu_hash_table *ght, ElfW(Word) hash,
                 ElfW(Sym) *sym, char *strtab);
