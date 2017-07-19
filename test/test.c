#include <stdio.h>

#include "test.h"
#include "../file.h"
#include "../lib.h"

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
