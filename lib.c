#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib.h"

/**
 * Print to stderr `msg` and exit the program execution
 * with EXIT_FAILURE.
 */
void err(char *msg)
{
    fprintf(stderr, "ERROR: %s\n", msg);
    exit(EXIT_FAILURE);
}

/**
 * Basic integer logging by displaying variable name and value
 */
void logint(char *name, int var)
{
    fprintf(stdout, "VARIABLE -- `%s`: %d -- (int)\n", name, var);
}

/**
 * Basic string logging by displaying variable name and value
 */
void logstr(char *name, char *str)
{
    fprintf(stdout, "STRING -- `%s`: %s -- (str)\n", name, str);
}

/**
 * Check if file exists and is readable and writable.
 * Don't allow files that don't have r/w access to be opened for now.
 * In the future we will probably allow users to open read only files.
 */
int fileExists(char *path)
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
 * Free up any linked list (single or double) of type hash_t by traversing
 * node list. This can either be used by nested hash_t structs that have
 * next/cur pointers or by simply casting structs as a hash_t as long
 * as they have hash_t *next as a member.
 * This has been checked with valgrind and should be good to go.
 */
void freeNodes(hash_t *head)
{
    hash_t *cur;
    hash_t *next;

    cur = head;

    while (cur->next != NULL)
        {
            next = cur->next;
            free(cur);
            cur = next;
        }

    /* When we're at this point we're at the last node */
    free(cur);
}
