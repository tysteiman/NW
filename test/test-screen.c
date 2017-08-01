#include "test-screen.h"
#include "test.h"

#include "../screen.h"

void
initScreenTestFile(file_t *file)
{
    clear();
    loadFile(file, NW_TEST_FILE);
    screen.cury = 0;
    screen.curx = 0;
    initScreen(file);
}

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
    NW_SCR_TEST();
    
    NW_MOVE_DOWN();
    
    NW_MOVE_TO_CUR();
    
    /* after we move we can use this to ensure our curx and cury are correct */
    NW_CUR();
    
    NW_SCR_CLOSE();

    NW_ASSERT(file->cursor.y, 1, "file cursor y is now at 1");
    NW_ASSERT(file->cursor.x, 0, "file cursor y remains at 0");
    NW_ASSERT(screen.cury, 1, "Screen current y is now at 1");
    NW_ASSERT(screen.curx, 0, "Screen current x remains at 0");
    NW_ASSERT(file->current->number, 2, "File line number is now at 2");
}

void
screenDeleteCharTest(file_t *file)
{
    NW_SCR_TEST();

    /* this is throwing the test off since this isn't implemented for screen yet */
    NW_MOVE_RIGHT(); NW_MOVE_RIGHT();

    NW_DEL();

    screenDeleteChar(file->current->content);

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 0, "Screen cury should stay at 0");
    NW_ASSERT(screen.curx, 2, "Screen curx should be at 2");

    /**
     * @TODO add more tests here mixing screen movement, etc
     */
}

/**
 * @TODO this needs to be updated since we removed all functionality
 *       away from screen & line. i think we need to make another file
 *       for handling BOTH at the same time. Screen should now just
 *       move and update the screen I think ... I don't know
 */
void
screenMoveLeftTest(file_t *file)
{
    NW_SCR_TEST();
    
    screenMoveRight(); screenMoveRight(); screenMoveRight();
    screenMoveLeft();
    
    NW_SCR_CLOSE();
    
    NW_ASSERT(screen.cury, 0, "Screen cur y remains at 0");
    NW_ASSERT(screen.curx, 2, "Screen cur x is at 2");
}

void
screenNewLineTest(file_t *file)
{
    NW_SCR_TEST();
    NW_SCR_CLOSE();
}
