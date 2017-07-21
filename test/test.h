#ifndef NW_TEST_H
#define NW_TEST_H

#include "../file.h"

#define NW_MAX_MESSAGE_LENGTH 200

/* Test library function decls */
void nw_assert(int real, int expected, char *msg, char *filename, int line, char *function, file_t *file);
void nw_assert_false(int real, int expected, char *msg, char *filename, int line, char *function, file_t *file);
void nw_assert_string(char *real, char *expected, char *msg, char *filename, int line, char *function, file_t *file);
void nw_assertion_error(char *filename, int line, char *function, char *msg, char *expectedResultMsg, file_t *file);

/**
 * This would represent a list of 'registered' test functions that are executed
 * when the test suite is invoked.
 */
void testFile     (file_t * file);
void loadFileTest (file_t * file);
void moveDownTest(file_t *file);
void moveUpTest(file_t *file);

#endif
