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
 *   syn.h
 *   
 *   Header file for syn.c (syntax libary)
 */

#ifndef NW_SYN_H
#define NW_SYN_H

#define NW_RUBY 1
#define NW_C 2
#define NW_TEXT 3

char * parseExtension               (char * fileName);
int    parseSyntaxFamilyByExtension (char * extension);

#endif
