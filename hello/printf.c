#include "printf.h"

void *get_auxv(char *envp[])
{
  while (envp && *envp)
    envp++;
  return !*envp ? envp++: envp;
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
  while (phdr && phdr->p_type != PT_NULL)
  {
    if (phdr->p_type == PT_DYNAMIC)
      return (void *)phdr->p_vaddr;
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
