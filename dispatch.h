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
 *   dispatch.h
 *
 */

#ifndef NW_DISPATCH_H
#define NW_DISPATCH_H

#include "file.h"

/* strings */
#define NW_KEY_DOWN "^N"        /* MOVE DOWN */
#define NW_KEY_UP "^P"          /* MOVE UP */
#define NW_KEY_LEFT "^B"        /* MOVE LEFT */
#define NW_KEY_RIGHT "^F"       /* MOVE RIGHT */
#define NW_KEY_END "^E"         /* MOVE TO END OF LINE */
#define NW_KEY_BEG "^A"         /* MOVE TO BEG OF LINE */
#define NW_KEY_EXIT "^C"        /* EXIT PROGRAM */
#define NW_KEY_SAVE "^S"        /* SAVE FILE */
#define NW_KEY_DEL "^D"         /* DELETE CHARACTER */
#define NW_KEY_DEL_LINE "^K"    /* DELETE LINE */
#define NW_KEY_NEW_LINE "^O"    /* CREATE NEW LINE BELOW CURSOR */
#define NW_KEY_JOIN_LINE "^U"   /* JOIN LINE TO ABOVE LINE */
#define NW_KEY_PAGE_DOWN "^V"   /* PAGE (SCROLL) DOWN */
#define NW_KEY_PAGE_UP "^Y"     /* PAGE (SCROLL) UP */
/* chars */
#define NW_KEY_RET '\n'         /* NEW LINE CHAR */
#define NW_KEY_TAB '\t'         /* TAB CHAR */
/* ints */
#define NW_KEY_BACKSPACE 127    /* BACKSPACE (ON DARWIN) */

#define NW_IS_JUNK_KEY() (c == -1)

void dispatchRight(file_t *file);
void dispatchLeft(file_t *file);
void dispatchEnd(file_t *file);
void dispatchBeg(file_t *file);
void dispatchInsert(char c, file_t *file);
void dispatchDeleteChar(file_t *file);
void dispatchDown(file_t *file);
void dispatchUp(file_t *file);
void dispatchNewLine(file_t *file);
void dispatchDeleteLine(file_t *file);
void dispatchSplitLine(file_t *file);
void dispatchJoinLine(file_t *file);
void dispatchPageDown(file_t *file);
void dispatchPageUp(file_t *file);

#endif
