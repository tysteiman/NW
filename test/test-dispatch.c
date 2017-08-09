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

#include "test-screen.h"
#include "test.h"

#include "../screen.h"
#include "../dispatch.h"

void
dispatchDownTest(file_t *file)
{
    /* use small file in test/lib */
    NW_SCR_TEST_SMALL();

    dispatchDown(file);
    dispatchEnd(file);
    dispatchDown(file);

    NW_SCR_CLOSE();

    /* curx should be at 20, xSnap at 30 still */
    NW_ASSERT(NW_CURY, 2, "cury is at 2");
    NW_ASSERT(NW_CURX, 20, "curx is at 20");
    NW_ASSERT(file->cursor.x, 20, "Cursor x at 20");
    NW_ASSERT(file->cursor.xSnap, 30, "xSnap is at 30");
}

void
dispatchJoinLineTest(file_t *file)
{
    NW_SCR_TEST_SMALL();

    dispatchDown(file);

    int moved = CURRENT->number;

    dispatchJoinLine(file);

    NW_SCR_CLOSE();

    NW_ASSERT(moved, 2, "After moving line number is 2");
    NW_ASSERT(CURRENT->number, 1, "Line number is now 1");
    NW_ASSERT(NW_CURY, 0, "CURY is now at 0");
    NW_ASSERT(file->cursor.y, 0, "cursor y is now at 0");
    NW_ASSERT(file->cursor.xSnap, 0, "cursor xSnap remains at 0");
    NW_ASSERT(file->cursor.x, 0, "cursor x remains at 0");
}

void
dispatchDeleteLineTest(file_t *file)
{
    NW_SCR_TEST_SMALL();

    dispatchDown(file);

    dispatchDeleteLine(file);

    NW_SCR_CLOSE();

    NW_ASSERT(CURRENT->number, 2, "Current line is 2");
    NW_ASSERT_STR(CURRENT->content, "", "Current content is empty");
    NW_ASSERT_STR(CURRENT->next->content, "This is a short line", "Next line content is correct");
    NW_ASSERT_STR(CURRENT->prev->content, "This is a line", "Prev line content is correct");

    NW_SCR_TEST_SMALL();

    dispatchDown(file);

    dispatchDeleteLine(file);

    dispatchUp(file);

    dispatchDown(file);

    NW_SCR_CLOSE();

    NW_ASSERT(CURRENT->number, 2, "Current line is 2");
    NW_ASSERT_STR(CURRENT->content, "", "Current content is empty");
    NW_ASSERT_STR(CURRENT->next->content, "This is a short line", "Next line content is correct");
    NW_ASSERT_STR(CURRENT->prev->content, "This is a line", "Prev line content is correct");
}
