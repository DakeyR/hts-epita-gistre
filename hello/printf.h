#include <link.h>

void *get_auxv(char *envp[]);
void *get_phdr(ElfW(auxv_t) *auxv);
void *get_dyn(ElfW(Phdr) *phdr);
void *get_rdebug(ElfW(Dyn) *dyn);
int call_printf(const char *format, ...);
