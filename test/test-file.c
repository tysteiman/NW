#include <stdlib.h>

#include "test.h"

/**
 * Assert the location of the current line
 */
void
loadFileTest(file_t *file)
{
    /* the line we start on in is line # 1 */
    NW_ASSERT(file->current->number, 1, "File starts on line # 1");

    NW_ASSERT_STR_NOT_NULL(file->name, "File name is not NULL");

    /* file is not edited */
    NW_ASSERT(file->edited, FALSE, "File's edited flag is FALSE");
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
            NW_ASSERT(file->cursor.y, y, "Cursor y position remains at the same point when only one line exists in file");

            /* x */
            NW_ASSERT(file->cursor.x, x, "Cursor x remains at the same point when only one line exists in file");
        }
    else
        {
            /* y */
            NW_ASSERT(file->cursor.y, y++, "Cursor y position moves one line down when next line is present");

            /* x */
            NW_ASSERT(file->cursor.x, x++, "Cursor x position moves one line down when next line is present");
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
            NW_ASSERT(file->cursor.y, y, "Cursor y position remains at the same point when only one line exists in file");

            /* x */
            NW_ASSERT(file->cursor.x, x, "Cursor x remains at the same point when only one line exists in file");
        }
    else
        {
            /* y */
            NW_ASSERT(file->cursor.y, y--, "Cursor y position moves one line down when next line is present");

            /* x */
            NW_ASSERT(file->cursor.x, x--, "Cursor x position moves one line down when next line is present");
        }

    if (file->totalLines > 1)
        {
            moveDown(file);
            moveDown(file);
            moveUp(file);

            NW_ASSERT(file->cursor.y, 1, "After moving down twice then up, cursor.y is at 1");
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
    NW_ASSERT(file->cursor.y, 1, "Cursor position y advances one line");
        
    /* line number advances one line */
    NW_ASSERT(file->current->number, 2, "Line number moves down one");
            
    /* Total number of lines increases by one */
    NW_ASSERT(file->totalLines, ++orgNoLines, "Total amount of lines increases by one");
}

void
xSnapTest(file_t *file)
{
    loadFile(file, NW_TEST_FILE);

    NW_MOVE_DOWN();
    NW_MOVE_END();

    int pos = file->cursor.x;

    NW_MOVE_DOWN();
    NW_MOVE_DOWN();
    NW_MOVE_DOWN();
    NW_MOVE_DOWN();
    NW_MOVE_DOWN();
    NW_MOVE_DOWN();

    NW_ASSERT(pos, 9, "Pos is correctly set.");
    NW_ASSERT(file->cursor.x, pos, "When moving through lines, xSnap should snap x pos to 9");
}