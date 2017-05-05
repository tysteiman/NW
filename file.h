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
    int x;
    int y;
} cursor_t;

typedef struct {
    char *name;       /* File Name */
    int totalLines;   /* Total number of lines in file */
    int edited;       /* Has file been edited & not saved? */
    line_t *lines;    /* line_t double lnk list of lines */
    line_t *current;  /* Pointer to current line */
    cursor_t cursor;  /* cursor_t cursor position on screen */
} file_t;

void loadFile (file_t *file, char *fileName);
void dumpFile (file_t *file);
void initializeEmptyNode (file_t *file);
void executeFileTests(file_t *file);

#endif
