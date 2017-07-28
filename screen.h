/**
 * screen.h
 *
 * This is intended to be the main header file for screen (terminal) functionality for
 * the NW editor. This should contain basic screen functions that can be considered
 * the "front end" of our application. NONE of these functions should be modifying the
 * contents of a file at any time. That is the whole point of our backend files like the
 * file.c & line.c files. Any logic contained here should be iterating through our lines
 * and matching the current process of our screen in general i.e. are we at the max,
 * should we repaint the screen, and how to update the front end version of our "file".
 */

#ifndef NW_SCREEN_H
#define NW_SCREEN_H

#include "file.h"

/**
 * The curx & cury attributes are NOT the same thing
 * as the cursor_t's x & y attributes. Our cursor's
 * values may be somewhere all the way down the page
 * however we need to track the square attributes of
 * our terminal, NOT in relation to the file itself.
 */
typedef struct {
    int maxx;    /* our screen's max X position */
    int maxy;    /* our screen's max Y position */
    int curx;    /* our screen's current X position */
    int cury;    /* our screen's current Y position */
    int resized; /* has our terminal been resized? */
} screen_t;

screen_t screen;

#define NW_SCR_INIT() (initScreen(&file))
/* keep our virtual cursor */
#define NW_CUR_SYNC() (move(file->cursor.y, file->cursor.x))
#define NW_PRINT(head) (printLines(head, file->totalLines))

/* DECLS */
void initScreen(file_t *file);
void printLines(line_t *start, int totalLines);

#endif
