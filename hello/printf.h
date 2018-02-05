#include <link.h>
#include <elf.h>

void *get_auxv(char *envp[]);
void *get_phdr(ElfW(auxv_t) *auxv);
void *get_dyn(ElfW(Phdr) *phdr);
void *get_rdebug(ElfW(Dyn) *dyn);
void *get_link_map(struct r_debug *dbg);
int call_printf(const char *format, ...);
