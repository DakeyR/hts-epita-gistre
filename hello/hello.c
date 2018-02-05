#include "printf.h"

int main(int argc, char *argv[], char *envp[])
{
  (void)argc;
  (void)argv;

  ElfW(auxv_t) *auxv = get_auxv(envp);
  return !auxv;

  return 0;
}
