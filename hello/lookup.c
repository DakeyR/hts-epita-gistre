#include "aux.h"
#include "lookup.h"

void *get_auxv(char *envp[])
{
  while (envp && *envp)
    envp++;
  return !(*envp) ? envp + 1 : envp;
}

void *get_phdr(ElfW(auxv_t) *auxv)
{
  while (auxv && auxv->a_type != AT_NULL)
  {
    if (auxv->a_type == AT_PHDR)
      return (void *)auxv->a_un.a_val;
    auxv++;
  }
  return (void *)0;
}

void *get_dyn(ElfW(Phdr) *phdr)
{
  ElfW(Addr) base = 0;
  while (phdr && phdr->p_type != PT_NULL)
  {
    if (phdr->p_type == PT_PHDR)
      base = (ElfW(Addr))phdr - phdr->p_vaddr;
    if (phdr->p_type == PT_DYNAMIC)
      return (void *)(phdr->p_vaddr + base);
    phdr++;
  }
  return (void *)0;
}

void *get_rdebug(ElfW(Dyn) *dyn)
{
  while (dyn && dyn->d_tag != DT_NULL)
  {
    if (dyn->d_tag == DT_DEBUG)
      return (void *)dyn->d_un.d_ptr;
    dyn++;
  }
  return (void *)0;
}

void *get_link_map(struct r_debug *dbg)
{
  return dbg ? dbg->r_map : (void *)0;
}

void *find_sym(const char *name, struct link_map *lm)
{

  while (lm)
  {
    ElfW(Dyn) *dyn = lm->l_ld;
    //struct gnu_hash_table *ght = (void *)0;
    ElfW(Sym) *sym = (void *)0;
    char *strtab = (void *)0;

    while (dyn && dyn->d_tag != DT_NULL)
    {
      ElfW(Addr) ptr = 0;
      if (dyn->d_un.d_ptr < lm->l_addr)
        ptr = lm->l_addr + dyn->d_un.d_ptr;
      else
        ptr = dyn->d_un.d_ptr;

      //if (dyn->d_tag == DT_GNU_HASH)
      //  ght = (void *)ptr;
      if (dyn->d_tag == DT_SYMTAB)
        sym = (void *)ptr;
      else if (dyn->d_tag == DT_STRTAB)
        strtab = (void *)ptr;
      if (sym && strtab)
        break;
      dyn++;
    }

    ElfW(Sym) *s = sym + 1;
#if 0
    if (ght)
    {
      ght->bloom = (ElfW(Xword) *)ght + 2;
      ght->buckets = (ElfW(Word) *)ght->bloom + ght->bloom_size * 2;
      ght->chain = (ElfW(Word) *)ght->buckets + ght->nbuckets;

      ElfW(Word) hash = gnu_hash((const unsigned char *)name);
      if (!is_absent(ght, hash))
      {
        while (1)
        {
          ElfW(Word) idx = ght->buckets[hash % ght->nbuckets];
          const char *n = (void*)(strtab + s[idx].st_name);
          const ElfW(Word) nhash = ght->chain[idx - ght->symoffset];

          if ((hash|1)== (nhash|1) && !my_strcmp(name, n))
            return (void *)lm->l_addr + s->st_value;

          if (nhash & 1)
            break;

          idx++;
        }
      }
    }
#endif

    while ((char *)s < strtab)
    {
      if (!my_strcmp(name, strtab + s->st_name))
        return (void *)lm->l_addr + s->st_value;
      s++;
    }

    lm = lm->l_next;
  }
  return (void *)0;
}
