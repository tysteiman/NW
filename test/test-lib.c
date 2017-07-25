#include "../lib.h"

#include "test.h"

void
fileExistsTest(file_t *file)
{
    /* fake path */
    int res = fileExists("foo.h");
    NW_ASSERT(res, FALSE, "File: foo.h does not exist");

    /* real path */
    int res2 = fileExists("nw.c");
    NW_ASSERT(res2, TRUE, "File: nw.c exists");
}

void
stringEqTest  (file_t * file)
{
    char *mainStr = "tyler";

    char *wrongStr = "kyler";
    char *correctStr = "tyler";

    /* assert wrong */
    int res_wrong = stringEq(mainStr, wrongStr);

    NW_ASSERT(res_wrong, FALSE, "kyler does not match tyler");

    /* assert correct */
    int res_correct = stringEq(mainStr, correctStr);

    NW_ASSERT(res_correct, TRUE, "tyler matches tyler");
}
