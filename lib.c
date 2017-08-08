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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "lib.h"

/**
 * Print to stderr `msg` and exit the program execution
 * with EXIT_FAILURE.
 */
void
err(char *msg)
{
    fprintf(stderr, "ERROR: %s\n", msg);
    exit(EXIT_FAILURE);
}

/**
 * Basic integer logging by displaying variable name and value
 */
void
logint(char *name, int var)
{
    fprintf(stdout, "VARIABLE -- `%s`: %d -- (int)\n", name, var);
}

/**
 * Basic string logging by displaying variable name and value
 */
void
logstr(char *name, char *str)
{
    fprintf(stdout, "STRING -- `%s`: %s -- (str)\n", name, str);
}

/**
 * Check if file exists and is readable and writable.
 * Don't allow files that don't have r/w access to be opened for now.
 * In the future we will probably allow users to open read only files.
 */
int
fileExists(char *path)
{
    if (access(path, R_OK|W_OK) != -1)
        {
            return TRUE;
        }
    else
        {
            return FALSE;
        }
}

/**
 * Wrap a string with color and print it to stderr
 */
void
colorStr(char *str, char *color)
{
    fprintf(stderr, "%s%s%s", color, str, NOCOLOR);
}

void
dumpDebug(char *msg)
{
    FILE *fp;
    fp = fopen("bin/DEBUG-FILE", "w");

    if (!fp)
        {
            err("Debug file could not be opened.");
        }

    fprintf(fp, "%s", msg);

    fclose(fp);
}

/**
 * Compare two strings and return TRUE if equal and FALSE
 * otherwise. We are not concerned about the difference
 * or anything between the two, just if they're literally
 * different or not.
 */
int
stringEq (char *str1,  char * str2)
{
    if (strcmp(str1, str2) == 0)
        {
            return TRUE;
        }
    else
        {
            return FALSE;
        }
}

char 
* 
substr(int start, int end, char *str)
{
    int i = start;
    int newStrIndex = 0;

    char newStr[MAX_LINE_LENGTH];

    for (; i < end + 1; i++)
        {
            newStr[newStrIndex] = str[i];
            newStrIndex++;
        }

    char *ret = strdup(newStr);
    ret[i] = '\0';

    return ret;
}
