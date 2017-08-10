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
 */

#ifndef NW_FILE
#define NW_FILE

#define NW_EMPTY_FILE "*empty*"

#define NW_UP 0
#define NW_DOWN 1

#include "lib.h"
#include "cursor.h"
#include "line.h"

typedef struct File {
    char *name;                    /* File Name */
    char *extension;               /* File extension */
    int syntax;                    /* Syntax group */
    int totalLines;                /* Total number of lines in file */
    int edited;                    /* Has file been edited & not saved? */
    line_t *lines;                 /* line_t double lnk list of lines */
    line_t *current;               /* Pointer to current line */
    cursor_t cursor;               /* cursor_t cursor position on screen */
} file_t;

file_t file;

#define NW_MOVE_UP() (moveUp(file))
#define NW_MOVE_DOWN() (moveDown(file))
#define NW_INCREASE_LINE_NUMBERS() (bumpLineNumbers(NW_UP, file->current->next))
#define NW_DECREASE_LINE_NUMBERS() (bumpLineNumbers(NW_DOWN, file->current->next))

#define CURRENT (file->current)
#define CURSOR (file->cursor)

void     loadFile            (file_t * file, char *fileName);
void     dumpFile            (file_t * file);
void     initializeEmptyNode (file_t * file);
int     saveFile            (file_t * file);
line_t * newLine             (file_t * file);
void     moveDown            (file_t * file);
void     moveUp              (file_t * file);
void     moveY               (file_t * file, int direction, int qual, int newY);
void     joinLine            (file_t * file);
void     bumpLineNumbers     (int direction, line_t *start);
void     splitLine           (file_t * file);

#endif
