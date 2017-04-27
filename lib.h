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
