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
    loadFileTest,
    moveDownTest,
    moveUpTest,
    newLineTest
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
            sprintf(expectedResults, "%sExpected: %s\tGot: %s\n\n%s", CYAN, expected, real, NOCOLOR);
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
    
    /**
     * Dump file if debug mode is on
     */
    if (opts.debug)
        {
            dumpFile(file);
        }
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

/**
 * Assert the location of the current line
 */
void
loadFileTest(file_t *file)
{
    /* the line we start on in is line # 1 */
    nw_assert(file->current->number, 1, "File starts on line # 1",
              __FILE__, __LINE__, (char *)__FUNCTION__, file);

    /* we don't have a null file name */
    nw_assert_false(file->name, NULL, "File name is not NULL",
                    __FILE__, __LINE__, (char *)__FUNCTION__, file);

    /* we don't have null current line ptr */
    nw_assert_false(file->current, NULL, "Current line ptr is not NULL",
                    __FILE__, __LINE__, (char *)__FUNCTION__, file);

    /* file is not edited */
    nw_assert(file->edited, FALSE, "File's edited flag is FALSE",
              __FILE__, __LINE__, (char *)__FUNCTION__, file);
}

/**
 * Test moving down a line
 */
void
moveDownTest(file_t *file)
{
    moveDown(file);

    int y;
    int x;

    y = file->cursor.y;
    x = file->cursor.x;

    if (file->current->number == file->totalLines)
        {
            /* y */
            nw_assert(file->cursor.y, y, "Cursor y position remains at the same point when only one line exists in file",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);

            /* x */
            nw_assert(file->cursor.x, x, "Cursor x remains at the same point when only one line exists in file",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);
        }
    else
        {
            /* y */
            nw_assert(file->cursor.y, y++, "Cursor y position moves one line down when next line is present",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);

            /* x */
            nw_assert(file->cursor.x, x++, "Cursor x position moves one line down when next line is present",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);
        }
}

/**
 * Test moving up
 */
void
moveUpTest(file_t *file)
{
    int y, x;
    
    y = file->cursor.y;
    x = file->cursor.x;
    
    moveUp(file);

    if (file->current->number == 1)
        {
            /* y */
            nw_assert(file->cursor.y, 0, "Cursor y position remains at the same point when only one line exists in file",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);

            /* x */
            nw_assert(file->cursor.x, x, "Cursor x remains at the same point when only one line exists in file",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);
        }
    else
        {
            /* y */
            nw_assert(file->cursor.y, y--, "Cursor y position moves one line down when next line is present",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);

            /* x */
            nw_assert(file->cursor.x, x--, "Cursor x position moves one line down when next line is present",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);
        }
}

/**
 * Test creating a newLine
 */
void
newLineTest(file_t *file)
{
    int orgNoLines = file->totalLines;
    
    newLine(file);
    
    /* cursor y position advances one line */
    nw_assert(file->cursor.y, 1, "Cursor position y advances one line",
            __FILE__, __LINE__, (char *)__FUNCTION__, file);
        
    /* line number advances one line */
    nw_assert(file->current->number, 2, "Line number moves down one",
            __FILE__, __LINE__, (char *)__FUNCTION__, file);
            
    /* Total number of lines increases by one */
    nw_assert(file->totalLines, ++orgNoLines, "Total amount of lines increases by one",
            __FILE__, __LINE__, (char *)__FUNCTION__, file);
}
