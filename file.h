#ifndef NW_FILE
#define NW_FILE

#define MAX_LINE_LENGTH 300
#define NW_EMPTY_FILE "*empty*"

#define NW_UP 0
#define NW_DOWN 1

#include "lib.h"

typedef struct Line {
    int number;                    /* Line number */
    int len;                       /* Line's length */
    char content[MAX_LINE_LENGTH]; /* Line's contents */
    struct Line *next;             /* Next Line in file */
    struct Line *prev;             /* Previous line in file */
} line_t;

/**
 * @TODO given how cursor works we can probably separate cursor and all
 *       related cursor functions over to its own implementation since
 *       we need to update xSnap however doing that depends on the length
 *       of the file line. Perhaps we can take them as integers instead
 *       of doing it as the entire file line information, when moving up
 *       or down we really just want to see if we're at the end of the line
 *       i.e. the current cursor position vs the amount of characters on the
 *       current line itself. When moving right we shouldn't care we should just
 *       be able to change the xSnap position.
 * @TODO when thinking about how our front end(s) will work with our file back end
 *       we need to think about how we'll dispatch front end events i.e. if the x
 *       position changes we should automatically update the front end instead of
 *       doing them separately. That's why it may be a good idea to never update
 *       backend cursor values without using some layer of abstraction to dispatch
 *       those events together. I'm thinking we can have a general movement() function
 *       where we can update the cursor position and just 'click' the front end into
 *       that position.
 */
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
void moveY                   (file_t *file, int direction, int qual, int newY);

#endif
