#include <stdio.h>

#include "test.h"

#include "test-file.h"
#include "test-lib.h"
#include "test-line.h"
#include "test-screen.h"
#include "test-dispatch.h"

#include "../file.h"
#include "../lib.h"
#include "../opt.h"

/**
 * Here is our array of pointer functions for the functions we want to
 * be included automatically in our test suite. In order to have a function
 * run, simply create the function and add it to this array and it will be ran.
 */
void (*tests[])(file_t *file) = {
    /* file */
    loadFileTest, newLineTest, moveDownTest, moveUpTest, xSnapTest,
    joinLineTest, splitLineTest,

    /* lib */
    fileExistsTest, stringEqTest,

    /* line */
    deleteCharTest, substrTest, moveRightTest, moveLeftTest,
    moveToLineEndTest, moveToLineBegTest, moveAndInsertCharDebug, clearLineTest,

    /* screen */
    initScreenTest, screenDeleteCharTest, screenMoveLeftTest, screenNewLineTest,
    screenMoveEndTest, screenMoveBegTest, screenMoveRightTest, screenMoveDownTest,
    screenInsertCharTest, screenDeleteLineTest,

    /* dispatch */
    dispatchDownTest
};

int nw_test_success = TRUE;

/**
 * @assert integer
 * Asserts `result' is true and if not displaying message with
 * file information. This is a 'simple' assertion meaning it just
 * makes sure we are at the point we want to be.
 */
void 
nw_assert(int real, int expected, char *msg, char *filename, int line, char *function, file_t *file)
{
    int result = real == expected;

    if (result == FALSE)
        {
            char expectedResults[NW_MAX_MESSAGE_LENGTH];
            sprintf(expectedResults, "%sExpected: %d\tGot: %d\n\n%s", CYAN, expected, real, NOCOLOR);
            nw_assertion_error(filename, line, function, msg, expectedResults, file);
        }
}

void
nw_assert_string_not_null(char *real, char *msg, char *filename, int line, char *function, file_t *file)
{
    int result = real != NULL;
    if (result == FALSE)
    {
        char expectedResults[NW_MAX_MESSAGE_LENGTH];
        sprintf(expectedResults, "%sExpected: NOT NULL\tGot: %s\n\n%s", CYAN, real, NOCOLOR);
        nw_assertion_error(filename, line, function, msg, expectedResults, file);
    }
}

/**
 * @assert integer
 * Asserts `result' is true and if not displaying message with
 * file information. This is a 'simple' assertion meaning it just
 * makes sure we are at the point we want to be.
 */
void 
nw_assert_false(int real, int expected, char *msg, char *filename, int line, char *function, file_t *file)
{
    int result = real != expected;

    if (result == FALSE)
        {
            char expectedResults[NW_MAX_MESSAGE_LENGTH];
            sprintf(expectedResults, "%sExpected: %d\tGot: %d\n\n%s", CYAN, expected, real, NOCOLOR);
            nw_assertion_error(filename, line, function, msg, expectedResults, file);
        }
}

/**
 * @assert string
 * Asserts `result' is true and if not displaying message with
 * file information. This is a 'simple' assertion meaning it just
 * makes sure we are at the point we want to be.
 */
void
nw_assert_string(char *real, char *expected, char *msg, char *filename, int line, char *function, file_t *file)
{
    int result = stringEq(real, expected);
    if (result == FALSE)
        {
            char expectedResults[NW_MAX_MESSAGE_LENGTH];
            sprintf(expectedResults, "%sExpected: '%s'\tGot: '%s'\n\n%s", CYAN, expected, real, NOCOLOR);
            nw_assertion_error(filename, line, function, msg, expectedResults, file);
        }
}

/**
 * Print assertion error encountered during test suite.
 */
void
nw_assertion_error(char *filename, int line, char *function, char *msg, char *expectedResultMsg, file_t *file)
{
    printf("\n%sERROR in %s:%d %s() %s %s%s\n", RED, filename, line, function, YELLOW, msg, NOCOLOR);
    printf("%s\n\n", expectedResultMsg);
    nw_test_success = FALSE;
}

/**
 * testFile is the main entry point for our test suite for our file.
 */
void 
testFile(file_t *file)
{
    printf("\n--------------------------------------------\n");
    printf("%sRUNNING TESTS FOR FILE: %s%s\n", CYAN, file->name, NOCOLOR);
    printf("--------------------------------------------\n");
    int i = 0;
    int size = sizeof(tests) / sizeof(void *);

    /**
     * For each of our test pointer functions we want to invoke it and load
     * the file cleanly again after that test. That way we have a fresh slate
     * at the beginning of each test without worrying about test state, etc.
     */
    for (; i < size; i++)
        {
            (*tests[i])(file);
            loadFile(file, opts.fileName);
        }

    if (nw_test_success)
        {
            printf("\n%sSUCCESS! ALL TESTS HAVE PASSED SUCCESSFULLY!%s\n\n", GREEN, NOCOLOR);
        }
}
