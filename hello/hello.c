#include "aux.h"
#include "printf.h"

typedef int (*fun)();

int main(int argc, char *argv[], char *envp[])
{
  (void)argc;
  (void)argv;

  ElfW(auxv_t) *auxv = get_auxv(envp);
  if (!auxv)
    return 1;

  ElfW(Phdr) *phdr = get_phdr(auxv);
  if (!phdr)
    return 2;

  ElfW(Dyn) *dyn = get_dyn(phdr);
  if (!dyn)
    return 3;

  struct r_debug *dbg = get_rdebug(dyn);
  if (!dbg)
    return 4;

  struct link_map *lm = get_link_map(dbg);
  if (!lm)
    return 5;

  void *f = find_sym("printf", lm);

  if (!f)
    return 6;

  ((fun) f)("Bonjour\n");

  return 0;
}
