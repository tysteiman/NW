#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib.h"

void err(char *msg)
{
    fprintf(stderr, "ERROR: %s\n", msg);
    exit(EXIT_FAILURE);
}

void logint(char *name, int var)
{
    fprintf(stdout, "VARIABLE -- `%s`: %d -- (int)\n", name, var);
}

int fileExists(char *path)
{
    if (access(path, F_OK) != -1) {
        return TRUE;
    } else {
        return FALSE;
    }
}
