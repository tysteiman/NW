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

#ifndef NW_TEST_FILE_H
#define NW_TEST_FILE_H

void loadFileTest      (file_t * file);
void moveDownTest      (file_t * file);
void moveUpTest        (file_t * file);
void newLineTest       (file_t * file);
void moveRightTest     (file_t * file);
void moveLeftTest      (file_t * file);
void moveToLineEndTest (file_t * file);
void moveToLineBegTest (file_t * file);
void xSnapTest         (file_t * file);
void joinLineTest      (file_t * file);
void splitLineTest     (file_t * file);

#endif
