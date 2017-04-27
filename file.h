#ifndef NW_FILE
#define NW_FILE

#define MAX_LINE_LENGTH 300

#include "lib.h"

typedef struct Line {
    int number;
    int len;
    char content[MAX_LINE_LENGTH];
    struct Line *next;
    struct Line *prev;
} line_t;

typedef struct {
    char *name;
    int totalLines;
    line_t *lines;
} file_t;

void loadFile (file_t *file, char *fileName);

#endif
