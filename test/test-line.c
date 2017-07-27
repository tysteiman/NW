#include "../lib.h"
#include "../opt.h"

#include "test.h"

/**
 * @TODO create a test using actual file->current->content data!
 */
void
deleteCharTest(file_t *file)
{
    /* load our test file */
    loadFile(file, NW_TEST_FILE);

    NW_MOVE_DOWN();
    // NW_MOVE_RIGHT();
    NW_DEL();

    NW_MOVE_RIGHT();
    NW_MOVE_RIGHT();

    NW_MOVE_BEG();

    NW_INS('z');

    NW_ASSERT_STR(file->current->content, "zdefine NW_LIB", "String should match input");
    
    NW_MOVE_DOWN();
    NW_MOVE_DOWN();
    NW_MOVE_END();
    NW_MOVE_LEFT();
    NW_MOVE_LEFT();
    
    NW_INS('T'); NW_INS('E'); NW_INS('S'); NW_INS('T'); NW_INS(' ');
    
    NW_ASSERT_STR(file->current->content, "/* CONSTANTS TEST */", "String should match input");

    /* first test (clip from middle) */
    /* char nameAr[MAX_LINE_LENGTH] = "Tyler"; */
    /* char *name = &nameAr[0]; */
    /* int x = file->cursor.x; */
    
    /* int len = file->current->len; */
    
    /* NW_MOVE_RIGHT(); */
    /* NW_MOVE_RIGHT(); */
    /* deleteChar(name, &file->cursor.x, &file->current->len); */

    /* NW_ASSERT_STR(name, "Tyer", "Deleting index 2 from Tyler results in Tyer"); */
    /* NW_ASSERT(file->current->len, --len, "Deleting from line decreases line len by 1."); */

    /* /\* third test (clip from beginning) *\/ */
    /* char thirdNameAr[MAX_LINE_LENGTH] = "Tyler"; */
    /* char *thirdName = &thirdNameAr[0]; */
    /* NW_MOVE_BEG(); */
    /* deleteChar(thirdName, &file->cursor.x, &file->current->len); */

    /* NW_ASSERT_STR(thirdName, "yler", "Deleting first index from Tyler results in yler"); */
    /* NW_ASSERT(file->current->len, --len, "Deleting from line decreases line len by 1."); */
}

/**
 * @TODO create a test using actual file->current->content data!
 */
void
insertCharTest(file_t *file)
{
    /* /\* insert in middle *\/ */
    /* char str[MAX_LINE_LENGTH] = "Tet"; */
    /* char *strP = &str[0]; */

    /* int len = file->current->len; */

    /* NW_MOVE_RIGHT(); */
    /* NW_MOVE_RIGHT(); */
    
    /* int x = file->cursor.x; */

    /* insertChar('s', strP, &file->cursor.x, &file->current->len); */

    /* NW_ASSERT_STR(strP, "Test", "Inserting a s at the 2nd index of Tet returns Test"); */
    /* NW_ASSERT(file->cursor.x, ++x, "Inserting a character should increase cursor x by 1"); */
    /* NW_ASSERT(file->current->len, ++len, "Inserting a char increases line len by 1"); */

    /* /\* insert in beginning *\/ */
    /* char str2[MAX_LINE_LENGTH] = "est"; */
    /* char *strP2 = &str2[0]; */

    /* NW_MOVE_BEG(); */

    /* x = file->cursor.x; */

    /* insertChar('T', strP2, &file->cursor.x, &file->current->len); */

    /* NW_ASSERT_STR(strP2, "Test", "Inserting a T at the beginning of est returns Test"); */
    /* NW_ASSERT(file->cursor.x, ++x, "Inserting a character should increase cursor x by 1"); */
    /* NW_ASSERT(file->current->len, ++len, "Inserting a char increases line len by 1"); */
}

void
moveAndInsertCharDebug(file_t *file)
{
    NW_MOVE_DOWN();
    NW_MOVE_RIGHT();
    NW_MOVE_RIGHT();

    insertChar('z', &file->current->content[0], &file->cursor.x, &file->current->len);

    NW_MOVE_DOWN();
    
    insertChar('t', &file->current->content[0], &file->cursor.x, &file->current->len);
    insertChar('y', &file->current->content[0], &file->cursor.x, &file->current->len);
    insertChar('l', &file->current->content[0], &file->cursor.x, &file->current->len);
    insertChar('e', &file->current->content[0], &file->cursor.x, &file->current->len);
    insertChar('r', &file->current->content[0], &file->cursor.x, &file->current->len);

    if (opts.debug)
        {
            dumpFile(file);
        }
}

void
substrTest(file_t *file)
{
    char * str = "Scuzbucket";

    char * res = substr(0, 3, str);
    NW_ASSERT_STR(res, "Scuz", "Substring 0-3 of Scuzbucket is Scuz");

    char * end = substr(4, 9, str);
    NW_ASSERT_STR(end, "bucket", "Substring 4-9 of Scuzbucket is bucket");
}

void
moveRightTest(file_t *file)
{
    /* test with cursor at 0 */
    int x = file->cursor.x;
    moveRight(file->current->len, &file->cursor);
    if (file->current->len > 0)
        {
            NW_ASSERT(file->cursor.x, ++x, "Moving right moves file->cursor.x by 1");
        }
}

void
moveLeftTest(file_t *file)
{
    /* test at beginning of line (0) */
    int x = file->cursor.x;
    // moveLeft(&file->cursor);
    NW_MOVE_LEFT();
    NW_ASSERT(file->cursor.x, x, "Moving left at pos 0 shouldn't move cursor.");

    /* test after moving */
    NW_MOVE_RIGHT();
    NW_MOVE_RIGHT();
    NW_MOVE_RIGHT();
    NW_MOVE_LEFT();
    if (file->current->len > 0)
        {
            NW_ASSERT(file->cursor.x, 2, "Moving right 3 times then left should make x = 2");
        }
}

void
moveToLineEndTest(file_t *file)
{
    int expect = file->current->len == 0 ? 0 : file->current->len;
    NW_MOVE_END();
    NW_ASSERT(file->cursor.x, expect, "Moving to end of line places x at end");
}

void
moveToLineBegTest(file_t *file)
{
    /* test before moving */
    NW_MOVE_BEG();
    NW_ASSERT(file->cursor.x, 0, "Moving to beginning of line while at 0 doesn't move cursor");
    
    /* test after moving */
    NW_MOVE_RIGHT();
    NW_MOVE_RIGHT();
    NW_MOVE_RIGHT();
    NW_MOVE_BEG();
    NW_ASSERT(file->cursor.x, 0, "Moving to beginning of the line places x at 0");
}
