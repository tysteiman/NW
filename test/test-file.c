#include <stdlib.h>

#include "test.h"

/**
 * Assert the location of the current line
 */
void
loadFileTest(file_t *file)
{
    /* the line we start on in is line # 1 */
    nw_assert(file->current->number, 1, "File starts on line # 1",
              __FILE__, __LINE__, (char *)__FUNCTION__, file);

    nw_assert_string_not_null(file->name, "File name is not NULL",
            __FILE__, __LINE__, (char *)__FUNCTION__, file);

    /* file is not edited */
    nw_assert(file->edited, FALSE, "File's edited flag is FALSE",
              __FILE__, __LINE__, (char *)__FUNCTION__, file);
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
            nw_assert(file->cursor.y, y, "Cursor y position remains at the same point when only one line exists in file",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);

            /* x */
            nw_assert(file->cursor.x, x, "Cursor x remains at the same point when only one line exists in file",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);
        }
    else
        {
            /* y */
            nw_assert(file->cursor.y, y++, "Cursor y position moves one line down when next line is present",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);

            /* x */
            nw_assert(file->cursor.x, x++, "Cursor x position moves one line down when next line is present",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);
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
            nw_assert(file->cursor.y, 0, "Cursor y position remains at the same point when only one line exists in file",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);

            /* x */
            nw_assert(file->cursor.x, x, "Cursor x remains at the same point when only one line exists in file",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);
        }
    else
        {
            /* y */
            nw_assert(file->cursor.y, y--, "Cursor y position moves one line down when next line is present",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);

            /* x */
            nw_assert(file->cursor.x, x--, "Cursor x position moves one line down when next line is present",
                      __FILE__, __LINE__, (char *)__FUNCTION__, file);
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
    nw_assert(file->cursor.y, 1, "Cursor position y advances one line",
            __FILE__, __LINE__, (char *)__FUNCTION__, file);
        
    /* line number advances one line */
    nw_assert(file->current->number, 2, "Line number moves down one",
            __FILE__, __LINE__, (char *)__FUNCTION__, file);
            
    /* Total number of lines increases by one */
    nw_assert(file->totalLines, ++orgNoLines, "Total amount of lines increases by one",
            __FILE__, __LINE__, (char *)__FUNCTION__, file);
}
