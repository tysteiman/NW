/**
 *   NW Editor - Super light terminal based editor
 *   Copyright (C) 2017 Tyler Steiman
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   screen.h
 *
 *   This is intended to be the main header file for screen (terminal) functionality for
 *   the NW editor. This should contain basic screen functions that can be considered
 *   the "front end" of our application. NONE of these functions should be modifying the
 *   contents of a file at any time. That is the whole point of our backend files like the
 *   file.c & line.c files. Any logic contained here should be iterating through our lines
 *   and matching the current process of our screen in general i.e. are we at the max,
 *   should we repaint the screen, and how to update the front end version of our "file".
 */

#ifndef NW_SCREEN_H
#define NW_SCREEN_H

#include "file.h"
#include <ncurses.h>

/**
 * The curx & cury attributes are NOT the same thing
 * as the cursor_t's x & y attributes. Our cursor's
 * values may be somewhere all the way down the page
 * however we need to track the square attributes of
 * our terminal, NOT in relation to the file itself.
 */
typedef struct Screen {
    int maxx;             /* our screen's max X position */
    int maxy;             /* our screen's max Y position */
    int curx;             /* our screen's current X position */
    int cury;             /* our screen's current Y position */
    int init_screen;
    void (*move_left)();  /* pointer to move left for screen */
    void (*move_right)(); /* pointer to move right */
    void (*move_up)();    /* pointer to move up */
    void (*move_down)();  /* pointer to move down */
    void (*move_end)();   /* pointer to move to end */
    void (*move_beg)();   /* pointer to move to beg */
} screen_t;

screen_t screen;

/* FUNCTION MACROS */
#define NW_SCR_INIT() (initScreen(&file))
/* keep our virtual cursor */
#define NW_CUR_SYNC() (move(file->cursor.y, file->cursor.x))
#define NW_CUR() (getyx(stdscr, screen.cury, screen.curx))
/* phyisically move to wherever our cury & curx is */
#define NW_MOVE_TO_CUR() (moveToCursor())
#define NW_PRINT(head) (printLines(head, file->totalLines))
#define NW_SCR_CLOSE() (endwin())
/* these are really just macros for directly calling move() */
#define NW_KEY_EQ(str) (stringEq(name, str))

/* print any single - line msg in center of screen */
#define NW_PRINT_CENTER(msg) (mvprintw(screen.maxy / 2, (screen.maxx / 2) - (strlen(msg) / 2), msg))

/* screen object macros */
#define NW_CURX (screen.curx)
#define NW_CURY (screen.cury)
#define NW_MAXY (screen.maxy - 1)
#define NW_MAXX (screen.maxx)

/* DECLS */
void initScreen(file_t *file);
void printLines(line_t *start, int totalLines);
void resizeScreen(file_t *file);
void screenDeleteChar(char *cur);
void screenMoveRight();
void screenMoveLeft();
void moveToCursor();
void screenNewLine(char *cur);
void screenMoveEnd();
void reprintLine(char *cur);
void screenMoveBeg();
void screenMoveDown();
void screenMoveUp();
void screenInsertChar();
void screenDeleteLine();
void screenScrollDown(file_t *file);
void screenScrollUp(line_t *head);
void screenSplitLine(file_t *file);
void screenJoinLine(file_t *file);
void printLine(char *head);

#endif
