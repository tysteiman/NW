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

#include "../lib.h"

#include "test.h"

void
fileExistsTest(file_t *file)
{
    /* fake path */
    int res = fileExists("foo.h");
    NW_ASSERT(res, FALSE, "File: foo.h does not exist");

    /* real path */
    int res2 = fileExists("nw.c");
    NW_ASSERT(res2, TRUE, "File: nw.c exists");
}

void
stringEqTest  (file_t * file)
{
    char *mainStr = "tyler";

    char *wrongStr = "kyler";
    char *correctStr = "tyler";

    /* assert wrong */
    int res_wrong = stringEq(mainStr, wrongStr);

    NW_ASSERT(res_wrong, FALSE, "kyler does not match tyler");

    /* assert correct */
    int res_correct = stringEq(mainStr, correctStr);

    NW_ASSERT(res_correct, TRUE, "tyler matches tyler");
}
