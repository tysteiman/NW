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

#ifndef NW_LIB
#define NW_LIB

/* CONSTANTS */
#define TRUE 1
#define FALSE 0

#define NOCOLOR "\033[0m"
#define RED "\033[91m"
#define GREEN "\033[92m"
#define YELLOW "\033[93m"
#define BLUE "\033[94m"
#define PURPLE "\033[95m"
#define CYAN "\033[96m"

#define MAX_LINE_LENGTH 300

/* scroll directions */
#define SCRL_UP -1
#define SCRL_DOWN 1

/* DECLS */
void err        (char * msg);
void logint     (char * name, int    var);
void logstr     (char * name, char * str);
void colorStr   (char * str,  char * color);
int  fileExists (char * path);
int  stringEq   (char * str1,  char * str2);
void dumpColors ();
void dumpDebug  (char * msg);
char * substr   (int start, int end, char *str);

#endif
