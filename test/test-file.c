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
            NW_ASSERT(file->cursor.y, 0, "Cursor y position remains at the same point when only one line exists in file");

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