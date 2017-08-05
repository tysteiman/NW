#ifndef NW_TEST_H
#define NW_TEST_H

#include "../file.h"

#define NW_MAX_MESSAGE_LENGTH 200
/* file to be used when we need actual file data to test */
#define NW_TEST_FILE "test/lib/test.h"
#define NW_TEST_FILE_SMALL "test/lib/small.txt"

/* Assertion function macros */
#define NW_ASSERT(real, expect, str)       (nw_assert(real, expect, str, __FILE__, __LINE__, (char *)__FUNCTION__, file))
#define NW_ASSERT_FALSE(real, expect, str) (nw_assert_false(real, expect, str, __FILE__, __LINE__, (char *)__FUNCTION__, file))
#define NW_ASSERT_STR(real, expect, str)   (nw_assert_string(real, expect, str, __FILE__, __LINE__, (char *)__FUNCTION__, file))
#define NW_ASSERT_STR_NOT_NULL(real, str)  (nw_assert_string_not_null(real, str, __FILE__, __LINE__, (char *)__FUNCTION__, file))

#define NW_TEST_SUCCESS() (printf("%s%s:%d\t\t%s()%s\n", GREEN, filename, line, function, NOCOLOR))

#define DEBUG() (printf("%sDebug for: %s:%d %s (%s)%s", RED, __FILE__, __LINE__, (void *)__FUNCTION__, file->name, NOCOLOR))

/* Test library function decls */
void nw_assert                 (int real, int expected, char *msg, char *filename, int line, char *function, file_t *file);
void nw_assert_false           (int real, int expected, char *msg, char *filename, int line, char *function, file_t *file);
void nw_assert_string          (char *real, char *expected, char *msg, char *filename, int line, char *function, file_t *file);
void nw_assert_string_not_null (char *real, char *msg, char *filename, int line, char *function, file_t *file);
void nw_assertion_error        (char *filename, int line, char *function, char *msg, char *expectedResultMsg, file_t *file);

/* main test 'controller' */
void testFile     (file_t * file);

#endif
