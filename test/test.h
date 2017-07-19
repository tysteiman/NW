#ifndef NW_TEST_H
#define NW_TEST_H

#include "../file.h"

/* Test library function decls */
void nw_assert(int result, char *msg, char *file, int line, char *function);

/**
 * This would represent a list of 'registered' test functions that are executed
 * when the test suite is invoked.
 */
void testFile     (file_t * file);
void loadFileTest (file_t * file);

#endif
