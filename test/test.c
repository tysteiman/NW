#include <stdio.h>

#include "test.h"
#include "../file.h"
#include "../lib.h"
#include "../opt.h"

/**
 * Here is our array of pointer functions for the functions we want to
 * be included automatically in our test suite. In order to have a function
 * run, simply create the function and add it to this array and it will be ran.
 */
void (*tests[])(file_t *file) = {
    loadFileTest
};

int nw_test_success = TRUE;

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
nw_assert(int result, char *msg, char *filename, int line, char *function, file_t *file)
{
    if (result == FALSE)
        {
            nw_test_success = FALSE;

            printf("%sERROR in %s:%d %s() %s %s%s\n", RED, filename, line, function, YELLOW, msg, NOCOLOR);

            /**
             * Dump file if debug mode is on
             */
            if (opts.debug)
                {
                    dumpFile(file);
                }
        }
}

/**
 * testFile is the main entry point for our test suite for our file.
 */
void 
testFile(file_t *file)
{

    int i = 0;
    int size = sizeof(tests) / sizeof(void *);

    /**
     * For each of our test pointer functions we want to invoke it and load
     * the file cleanly again after that test. That way we have a fresh slate
     * at the beginning of each test without worrying about test state, etc.
     */
    for (i; i < size; i++)
        {
            (*tests[i])(file);
            loadFile(file, opts.fileName);
        }

    if (nw_test_success)
        {
            printf("%sSUCCESS! ALL TESTS HAVE PASSED SUCCESSFULLY!%s\n", GREEN, NOCOLOR);
        }
}

/**
 * Assert the location of the current line
 */
void
loadFileTest(file_t *file)
{
    /* the line we start on in is line # 1 */
    nw_assert((file->current->number == 1), "File starts on line # 1", __FILE__, __LINE__, __FUNCTION__, file);
}
