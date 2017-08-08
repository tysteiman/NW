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

#ifndef NW_TEST_SCREEN_H
#define NW_TEST_SCREEN_H

#include "../file.h"

#define NW_SCR_TEST() (initScreenTestFile(file, NW_TEST_FILE))
#define NW_SCR_TEST_SMALL() (initScreenTestFile(file, NW_TEST_FILE_SMALL))

void initScreenTestFile(file_t *file, char *fileName);
void initScreenTest(file_t *file);
void screenDeleteCharTest(file_t *file);
void screenMoveDownTest(file_t *file);
void screenMoveLeftTest(file_t *file);
void screenNewLineTest(file_t *file);
void screenMoveEndTest(file_t *file);
void screenMoveBegTest(file_t *file);
void screenMoveRightTest(file_t *file);
void screenInsertCharTest(file_t *file);
void screenDeleteLineTest(file_t *file);

#endif
