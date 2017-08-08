/**
 * syn.c
 *
 * Implementation file for all syntax specific functionality pertaining to
 * functionality given a certain file type. The main goal for this library
 * is really small things like setting opts.tabWidth based on certain file
 * types since we will not be building out complex syntax-specific functionality
 * in the NW editor.
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
