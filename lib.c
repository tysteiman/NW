#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib.h"

/**
 * @TODO create library for linked lists. this should probably include
 * freeing nodes for both linked & double linked lists, adding new
 * elements to the list, etc. Maybe create another pointer function
 * for each struct type that can add all the attributes of that
 * struct since they'll all contain different attributes.
 */

void err(char *msg)
{
    fprintf(stderr, "ERROR: %s\n", msg);
    exit(EXIT_FAILURE);
}

void logint(char *name, int var)
{
    fprintf(stdout, "VARIABLE -- `%s`: %d -- (int)\n", name, var);
}

void logstr(char *name, char *str)
{
    fprintf(stdout, "STRING -- `%s`: %s -- (str)\n", name, str);
}

int fileExists(char *path)
{
    /**
     * Don't allow files that don't have r/w access to be opened for now.
     * In the future we will probably allow users to open read only files.
     */
    if (access(path, R_OK|W_OK) != -1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

