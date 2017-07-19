#include <stdio.h>

#include "test.h"
#include "../file.h"
#include "../lib.h"

/**
 * Asserts `result' is true and if not displaying message with
 * file information. This is a 'simple' assertion meaning it just
 * makes sure we are at the point we want to be. We probably need
 * more information than this in reality in terms of displaying
 * the actual values? Maybe also pass the 'thing' we're checking
 * the value of (assert file->cursor.x == 3 by passing file->cursor.x
 * to the function as an argument itself).
 */
void 
nw_assert(int result, char *msg, char *file)
{
    if (result == FALSE)
        {
            printf("%sERROR in %s: %s%s\n", RED, file, msg, NOCOLOR);
        }
}

void 
testFile(file_t *file)
{
    nw_assert((5==3), "Five equals three", __FILE__);
}
