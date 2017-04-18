#include <stdio.h>
#include <stdlib.h>

void err(char *msg)
{
  fprintf(stderr, "ERROR: %s\n", msg);
  exit(EXIT_FAILURE);
}

void logint(char *name, int var)
{
  fprintf(stdout, "VARIABLE -- `%s`: %d -- (int)\n", name, var);
}
