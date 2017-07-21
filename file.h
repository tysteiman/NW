#ifndef NW_FILE
#define NW_FILE

#define MAX_LINE_LENGTH 300
#define NW_EMPTY_FILE "*empty*"

#include "lib.h"

typedef struct Line {
    int number;                    /* Line number */
    int len;                       /* Line's length */
    char content[MAX_LINE_LENGTH]; /* Line's contents */
    struct Line *next;             /* Next Line in file */
    struct Line *prev;             /* Previous line in file */
} line_t;

typedef struct {
    int x;                         /* Current cursor x pos */
    int xSnap;                     /* Value we should snap back to when moving */
    int y;                         /* Current cursor y pos */
} cursor_t;

typedef struct {
    char *name;                    /* File Name */
    char *extension;               /* File extension */
    int totalLines;                /* Total number of lines in file */
    int edited;                    /* Has file been edited & not saved? */
    line_t *lines;                 /* line_t double lnk list of lines */
    line_t *current;               /* Pointer to current line */
    cursor_t cursor;               /* cursor_t cursor position on screen */
} file_t;

file_t file;

void     loadFile            (file_t * file, char *fileName);
void     dumpFile            (file_t * file);
void     initializeEmptyNode (file_t * file);
void     saveFile            (file_t * file);
line_t * newLine             (file_t * file);
void moveDown                (file_t * file);
void moveUp                  (file_t * file);

#endif
