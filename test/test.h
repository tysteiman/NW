#ifndef NW_TEST_H
#define NW_TEST_H

#include "../file.h"

#define NW_MAX_MESSAGE_LENGTH 200
#define NW_TEST_FILE "test/lib/test.h"

/* Assertion function macros */
#define NW_ASSERT(real, expect, str)       (nw_assert(real, expect, str, __FILE__, __LINE__, (char *)__FUNCTION__, file))
#define NW_ASSERT_FALSE(real, expect, str) (nw_assert_false(real, expect, str, __FILE__, __LINE__, (char *)__FUNCTION__, file))
#define NW_ASSERT_STR(real, expect, str)   (nw_assert_string(real, expect, str, __FILE__, __LINE__, (char *)__FUNCTION__, file))
#define NW_ASSERT_STR_NOT_NULL(real, str)  (nw_assert_string_not_null(real, str, __FILE__, __LINE__, (char *)__FUNCTION__, file))

/* Test library function decls */
void nw_assert                 (int real, int expected, char *msg, char *filename, int line, char *function, file_t *file);
void nw_assert_false           (int real, int expected, char *msg, char *filename, int line, char *function, file_t *file);
void nw_assert_string          (char *real, char *expected, char *msg, char *filename, int line, char *function, file_t *file);
void nw_assert_string_not_null (char *real, char *msg, char *filename, int line, char *function, file_t *file);

void nw_assertion_error        (char *filename, int line, char *function, char *msg, char *expectedResultMsg, file_t *file);

void testFile     (file_t * file);

#endif
