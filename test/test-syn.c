#include "test.h"
#include "../syn.h"

void
parseFileExtensionTest(file_t *file)
{
    /* rb */
    char *testFile = "/Users/foo/proj/ruby_file.rb";
    char *res = parseExtension(testFile);

    NW_ASSERT_STR(res, "rb", "Extension of ruby_file.rb is rb");

    /* c */
    char *cTest = "~/test.c";
    char *cRes = parseExtension(cTest);

    NW_ASSERT_STR(cRes, "c", "Extension of ~/test.c is c");

    /* sh */
    char *shTest = "~/.file.sh";
    char *shRes = parseExtension(shTest);

    NW_ASSERT_STR(shRes, "sh", "Extension of ~/.file.sh is sh");
}
