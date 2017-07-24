#include "../lib.h"

#include "test.h"

void
fileExistsTest(file_t *file)
{
    /* fake path */
    int res = fileExists("foo.h");
    nw_assert(res, FALSE, "File: foo.h does not exist",
            __FILE__, __LINE__, (char *)__FUNCTION__, file);

    /* real path */
    int res2 = fileExists("nw.c");
    nw_assert(res2, TRUE, "File: nw.c exists",
            __FILE__, __LINE__, (char *)__FUNCTION__, file);            
}