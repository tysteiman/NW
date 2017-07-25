#include "../lib.h"
#include "test.h"

void deleteCharTest(file_t *file)
{
    /* first test (clip from middle) */
    char nameAr[MAX_LINE_LENGTH] = "Tyler";
    char *name = &nameAr[0];
    deleteChar(name, 2);

    NW_ASSERT_STR(name, "Tyer", "Deleting index 2 from Tyler results in Tyer");

    /* second test (clip from end) */
    char secondNameAr[MAX_LINE_LENGTH] = "Tyler";
    char *secondName = &secondNameAr[0];
    deleteChar(secondName, 4);

    NW_ASSERT_STR(secondName, "Tyle", "Deleting from end of Tyler results in Tyle");

    /* third test (clip from beginning) */
    char thirdNameAr[MAX_LINE_LENGTH] = "Tyler";
    char *thirdName = &thirdNameAr[0];
    deleteChar(thirdName, 0);

    NW_ASSERT_STR(thirdName, "yler", "Deleting first index from Tyler results in yler");
}

void insertCharTest(file_t *file)
{
    /* insert in middle */
    char str[MAX_LINE_LENGTH] = "Tet";
    char *strP = &str[0];

    insertChar('s', strP, 2);

    NW_ASSERT_STR(strP, "Test", "Inserting a s at the 2nd index of Tet returns Test");

    /* insert in beginning */
    char str2[MAX_LINE_LENGTH] = "est";
    char *strP2 = &str2[0];

    insertChar('T', strP2, 0);

    NW_ASSERT_STR(strP2, "Test", "Inserting a T at the beginning of est returns Test");

    /* insert at end */
    char str3[MAX_LINE_LENGTH] = "Tes";
    char *strP3 = &str3[0];

    insertChar('t', strP3, 3);

    NW_ASSERT_STR(strP3, "Test", "Inserting a T at the beginning of est returns Test");
}

void substrTest(file_t *file)
{
    char * str = "Scuzbucket";

    char * res = substr(0, 3, str);
    NW_ASSERT_STR(res, "Scuz", "Substring 0-3 of Scuzbucket is Scuz");

    char * end = substr(4, 9, str);
    NW_ASSERT_STR(end, "bucket", "Substring 4-9 of Scuzbucket is bucket");
}
