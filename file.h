#ifndef NW_FILE
#define NW_FILE

#define MAX_LINE_LENGTH 300

#include "lib.h"

typedef struct Line {
    int number;
    int len;
    char content[MAX_LINE_LENGTH];
    hash_t nodes;
} line_t;

typedef struct {
    char *name;
    int totalLines;
    line_t *lines;
} file_t;

file_t newFile  (char *fileName);
file_t loadFile (char *fileName);

#endif

