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

#define NW_KEY_DOWN "^N"
#define NW_KEY_UP "^P"
#define NW_KEY_LEFT "^B"
#define NW_KEY_RIGHT "^F"
#define NW_KEY_END "^E"
#define NW_KEY_BEG "^A"
#define NW_KEY_EXIT "^C"
#define NW_KEY_SAVE "^S"
#define NW_KEY_DEL "^D"
#define NW_KEY_DEL_LINE "^K"
#define NW_KEY_NEW_LINE "^O"
#define NW_KEY_JOIN_LINE "^J"
#define NW_KEY_RET '\n'
#define NW_KEY_TAB '\t'

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

#endif
