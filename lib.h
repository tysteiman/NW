/**
 * lib.h
 * The main shared library of the NW editor. This is used mainly for global functions
 * that need to be used throughout the repository. A good example of this is basic
 * linked list operations like freeNodes, logging, and other helper/shared functions.
 */

#ifndef NW_LIB
#define NW_LIB

/* CONSTANTS */
#define TRUE 1
#define FALSE 0

/* STRUCTS */
typedef struct Hash {
    struct Hash *next;
    struct Hash *prev;
} hash_t;

/* DECLS */
void err        (char *msg);
void logint     (char *name, int var);
void logstr     (char *name, char *str);
int  fileExists (char *path);
void freeNodes  (hash_t *head);

#endif

