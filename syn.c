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
 *   syn.c
 *   
 *   Implementation file for all syntax specific functionality pertaining to
 *   functionality given a certain file type. The main goal for this library
 *   is really small things like setting opts.tabWidth based on certain file
 *   types since we will not be building out complex syntax-specific functionality
 *   in the NW editor.
 */

#include <string.h>

#include "syn.h"
#include "lib.h"

/**
 * Parse a file name and return a char ptr of the parsed extension. This
 * works with dot files, as it simply continues to set the index of a found
 * dot up until the last one is found.
 */
char
*
parseExtension(char *fileName)
{
    char *res;
    
    int i = 0;
    int index = -1;

    for (; i < strlen(fileName); i++)
        {
            /**
             * By doing this we can accept dot files like ~/.file.sh and parse
             * them correctly since the final index below will get set to the last
             * dot, not the first. It will hit the first, set the index, and continue
             * on until the last, setting the index correctly. This may only work for
             * conventional files, appending .bak to the file will blow this up.
             */
            if (fileName[i] != '.')
                {
                    continue;
                }
            else
                {
                    index = i;
                }
        }

    if (index != -1)
        {
            res = substr(++index, strlen(fileName), fileName);
        }

    return res;
}

int
parseSyntaxFamilyByExtension(char *extension)
{
    /**
     * @TODO This needs to be completely changed into a system that makes sense.
     *       this lazy way is fine since we only care about ruby right now.
     */
    if (stringEq(extension, "rb"))
        {
            return NW_RUBY;
        }
    else
        {
            return NW_TEXT;
        }
}