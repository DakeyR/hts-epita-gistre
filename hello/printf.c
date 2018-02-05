#include "printf.h"

void *get_auxv(char *envp[])
{
  while (envp && *envp)
    envp++;
  return envp;
}
