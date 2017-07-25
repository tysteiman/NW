#include "../lib.h"
#include "test.h"

void deleteCharTest(file_t *file)
{
    char nameAr[MAX_LINE_LENGTH] = "Tyler";

    char *name = &nameAr[0];

    deleteChar(name, 2);

    nw_assert_string(name, "Tyer", "Deleting index 2 from Tyler results in Tyer",
                     __FILE__, __LINE__, (char *)__FUNCTION__, file);
}

void substrTest(file_t *file)
{
    char * str = "Scuzbucket";

    char * res = substr(0, 3, str);
    nw_assert_string(res, "Scuz", "Substring 0-3 of Scuzbucket is Scuz",
                     __FILE__, __LINE__, (char *)__FUNCTION__, file);

    char * end = substr(4, 9, str);
    nw_assert_string(end, "bucket", "Substring 4-9 of Scuzbucket is bucket",
                     __FILE__, __LINE__, (char *)__FUNCTION__, file);
}
