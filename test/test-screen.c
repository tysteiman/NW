#include "test-screen.h"
#include "test.h"

#include "../screen.h"

void 
initScreenTest(file_t *file)
{
    /* test screen initialization */
    loadFile(file, NW_TEST_FILE);
    initScreen(file);
    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 0, "screen.cury initialized to 0");
    NW_ASSERT(screen.curx, 0, "screen.curx initialized to 0");
    NW_ASSERT(file->cursor.x, 0, "cursor.x remains at 0");
    NW_ASSERT(file->cursor.y, 0, "cursor.y remains at 0");
    NW_ASSERT(file->current->number, 1, "Current file number remains at 1");
}

void
screenMoveDownTest(file_t *file)
{
    loadFile(file, NW_TEST_FILE);
    initScreen(file);

    NW_SCR_CLOSE();

    // NW_SCR_MOVE_DOWN();
    NW_MOVE_DOWN();
    NW_SCR_MOVE_DOWN();

    NW_ASSERT(file->cursor.y, 1, "file cursor y is now at 1");
    NW_ASSERT(file->cursor.x, 0, "file cursor y remains at 0");
    NW_ASSERT(screen.cury, 1, "Screen current y is now at 1");
    NW_ASSERT(screen.curx, 0, "Screen current x remains at 0");
    NW_ASSERT(file->current->number, 2, "File line number is now at 2");
}