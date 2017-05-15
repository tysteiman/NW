#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib.h"

/**
 * Print to stderr `msg` and exit the program execution
 * with EXIT_FAILURE.
 */
void
err(char *msg)
{
    fprintf(stderr, "ERROR: %s\n", msg);
    exit(EXIT_FAILURE);
}

/**
 * Basic integer logging by displaying variable name and value
 */
void
logint(char *name, int var)
{
    fprintf(stdout, "VARIABLE -- `%s`: %d -- (int)\n", name, var);
}

/**
 * Basic string logging by displaying variable name and value
 */
void
logstr(char *name, char *str)
{
    fprintf(stdout, "STRING -- `%s`: %s -- (str)\n", name, str);
}

/**
 * Check if file exists and is readable and writable.
 * Don't allow files that don't have r/w access to be opened for now.
 * In the future we will probably allow users to open read only files.
 */
int
fileExists(char *path)
{
    if (access(path, R_OK|W_OK) != -1)
        {
            return TRUE;
        }
    else
        {
            return FALSE;
        }
}

/**
 * Wrap a string with color and print it to stderr
 */
void
colorStr(char *str, char *color)
{
    fprintf(stderr, "%s%s%s", color, str, NOCOLOR);
}

void
dumpColors()
{
    int i;
    i = 1;
    
    for (; i < 300; i++)
        {
            printf("%d: \033[%dmTHIS IS A COLOR!\033[0m\n", i, i);
        }
}
