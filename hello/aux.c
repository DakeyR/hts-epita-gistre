#include "aux.h"

int my_strcmp(const char *str1, const char *str2)
{
  while (*str1 && *str2)
  {
    if (*str1 < *str2)
      return -1;
    if (*str1 > *str2)
      return 1;
    str1++;
    str2++;
  }

  if (*str1 == *str2)
    return 0;
  if (!*str1)
    return -1;
  return 1;
}

int is_absent(struct gnu_hash_table *ght, ElfW(Word) hash)
{
  if (!ght)
    return 0;
  ElfW(Xword) word = ght->bloom[(hash / __ELF_NATIVE_CLASS) % ght->bloom_size];
  ElfW(Xword) mask = 0 
          | (ElfW(Xword))1 << (hash % __ELF_NATIVE_CLASS) 
          | (ElfW(Xword))1 << (hash >> ght->bloom_shift) % __ELF_NATIVE_CLASS;

  if ((word & mask) != mask)
    return 0;
  return 1;
}

void *lookup_sym(struct gnu_hash_table *ght, ElfW(Word) hash,
                 ElfW(Sym) *sym, char *strtab)
{
  if (!ght || !sym)
    return 0;

  ElfW(Word) idx = ght->buckets[hash % ght->nbuckets];
  ElfW(Sym) *s = sym + idx;

  (void)strtab;

  //if (s)
  //  char *name = strtab + s->st_name;
  return s;
}
