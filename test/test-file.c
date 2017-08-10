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

#include <stdlib.h>

#include "test.h"

/**
 * Assert the location of the current line
 */
void
loadFileTest(file_t *file)
{
    /* the line we start on in is line # 1 */
    NW_ASSERT(file->current->number, 1, "File starts on line # 1");

    NW_ASSERT_STR_NOT_NULL(file->name, "File name is not NULL");

    /* file is not edited */
    NW_ASSERT(file->edited, FALSE, "File's edited flag is FALSE");

    /* xSnap is 0 */
    NW_ASSERT(CURSOR.xSnap, 0, "xSnap value is initialized to 0");

    /* file->lines->number is 1 */
    NW_ASSERT(file->lines->number, 1, "File lines number is at 1");
}

/**
 * Test moving down a line
 */
void
moveDownTest(file_t *file)
{
    moveDown(file);

    int y;
    int x;

    y = CURSOR.y;
    x = CURSOR.x;

    if (file->current->number == file->totalLines)
        {
            /* y */
            NW_ASSERT(CURSOR.y, y, "Cursor y position remains at the same point when only one line exists in file");

            /* x */
            NW_ASSERT(CURSOR.x, x, "Cursor x remains at the same point when only one line exists in file");
        }
    else
        {
            /* y */
            NW_ASSERT(CURSOR.y, y++, "Cursor y position moves one line down when next line is present");

            /* x */
            NW_ASSERT(CURSOR.x, x++, "Cursor x position moves one line down when next line is present");
        }
}

/**
 * Test moving up
 */
void
moveUpTest(file_t *file)
{
    int y, x;
    
    y = CURSOR.y;
    x = CURSOR.x;
    
    moveUp(file);

    if (file->current->number == 1)
        {
            /* y */
            NW_ASSERT(CURSOR.y, y, "Cursor y position remains at the same point when only one line exists in file");

            /* x */
            NW_ASSERT(CURSOR.x, x, "Cursor x remains at the same point when only one line exists in file");
        }
    else
        {
            /* y */
            NW_ASSERT(CURSOR.y, y--, "Cursor y position moves one line down when next line is present");

            /* x */
            NW_ASSERT(CURSOR.x, x--, "Cursor x position moves one line down when next line is present");
        }

    if (file->totalLines > 1)
        {
            moveDown(file);
            moveDown(file);
            moveUp(file);

            NW_ASSERT(CURSOR.y, 1, "After moving down twice then up, cursor.y is at 1");
        }
}

/**
 * Test creating a newLine
 */
void
newLineTest(file_t *file)
{
    int orgNoLines = file->totalLines;
    
    newLine(file);
    
    /* cursor y position advances one line */
    NW_ASSERT(CURSOR.y, 1, "Cursor position y advances one line");
        
    /* line number advances one line */
    NW_ASSERT(file->current->number, 2, "Line number moves down one");
            
    /* Total number of lines increases by one */
    NW_ASSERT(file->totalLines, ++orgNoLines, "Total amount of lines increases by one");

    loadFile(file, NW_TEST_FILE);

    NW_MOVE_END();
    newLine(file);

    NW_INS('/'); NW_INS('/'); NW_INS(' '); NW_INS('T'); NW_INS('E'); NW_INS('S'); NW_INS('T');

    NW_ASSERT_STR(file->current->content, "// TEST", "New line's content matches // TEST");
}

void
xSnapTest(file_t *file)
{
    loadFile(file, NW_TEST_FILE);

    NW_MOVE_DOWN();
    NW_MOVE_END();

    int pos = CURSOR.x;

    NW_MOVE_DOWN();
    NW_MOVE_DOWN();
    NW_MOVE_DOWN();
    NW_MOVE_DOWN();
    NW_MOVE_DOWN();
    NW_MOVE_DOWN();

    NW_ASSERT(pos, 9, "Pos is correctly set.");
    NW_ASSERT(CURSOR.x, pos, "When moving through lines, xSnap should snap x pos to 9");
}

void
joinLineTest(file_t *file)
{
    loadFile(file, NW_TEST_FILE);

    /* test when line is empty (no content to append) */
    NW_MOVE_DOWN(); NW_MOVE_DOWN(); NW_MOVE_DOWN();
    NW_MOVE_DOWN(); NW_MOVE_DOWN(); NW_MOVE_DOWN();

    int expTotal = file->totalLines - 1;
    int expLine = file->current->prev->number;
    int expX = file->current->prev->len;

    joinLine(file);

    NW_ASSERT_STR(file->current->content, " */", "New current line has no added content");
    NW_ASSERT(file->totalLines, expTotal, "File's total lines decreases by 1");
    NW_ASSERT(file->current->number, expLine, "New current line is previous number's");
    NW_ASSERT(CURSOR.x, 0, "Cursor is at 0");

    /* test when current line has content (should append to prev) */
    NW_MOVE_DOWN();
    NW_MOVE_DOWN();
    NW_MOVE_DOWN();
    NW_MOVE_DOWN();
    NW_MOVE_DOWN();
    NW_MOVE_BEG();
    joinLine(file);

    NW_ASSERT_STR(file->current->content, "/* CONSTANTS */#define TRUE 1", "properly appends text to prev line when present");
}

void
splitLineTest(file_t *file)
{
    loadFile(file, NW_TEST_FILE);

    /* split in middle of line */
    NW_MOVE_DOWN(); NW_MOVE_DOWN(); NW_MOVE_DOWN(); NW_MOVE_DOWN(); NW_MOVE_DOWN();
    NW_MOVE_DOWN(); NW_MOVE_DOWN(); NW_MOVE_DOWN(); NW_MOVE_DOWN(); NW_MOVE_DOWN();

    NW_MOVE_RIGHT(); NW_MOVE_RIGHT(); NW_MOVE_RIGHT();
    NW_MOVE_RIGHT(); NW_MOVE_RIGHT(); NW_MOVE_RIGHT();

    char *l1 = "/* CON";
    char *l2 = "STANTS */";

    splitLine(file);

    NW_ASSERT_STR(file->current->prev->content, l1, "Previous line equals l1");
    NW_ASSERT_STR(file->current->content, l2, "Current line now contains l2");
    NW_ASSERT(file->current->len, 9, "Current line len should be 9");
    NW_ASSERT(CURSOR.x, 0, "Cursor x should be at 0");
    NW_ASSERT(CURSOR.xSnap, 0, "Cursor xSnap should be at 0");

    NW_MOVE_DOWN();
    NW_MOVE_DOWN();
    NW_MOVE_END();

    char *l3 = "#define FALSE 0";
    char *l4 = "";

    /* split at end (should just create new line) */
    splitLine(file);

    NW_ASSERT_STR(file->current->prev->content, l3, "Previous line equals l3");
    NW_ASSERT_STR(file->current->content, l4, "Current line should be empty");
    NW_ASSERT(file->current->len, 0, "Current line len should be 0");
    NW_ASSERT(CURSOR.x, 0, "Cursor x should be at 0");
    NW_ASSERT(CURSOR.xSnap, 0, "Cursor xSnap should be at 0");

    /* split at beginning of line (should have current line be full prev) */
    NW_MOVE_UP();

    char *l5 = "";
    char *l6 = "#define FALSE 0";

    splitLine(file);

    NW_ASSERT_STR(file->current->prev->content, l5, "Previous line equals l5 (empty)");
    NW_ASSERT_STR(file->current->content, l6, "Current line should be full content of l6");
    NW_ASSERT(file->current->len, 15, "Current line len should be 15");
    NW_ASSERT(CURSOR.x, 0, "Cursor x should be at 0");
    NW_ASSERT(CURSOR.xSnap, 0, "Cursor xSnap should be at 0");
}
