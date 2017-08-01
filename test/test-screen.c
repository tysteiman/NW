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
screenDeleteCharTest(file_t *file)
{
    NW_SCR_TEST();

    /* this is throwing the test off since this isn't implemented for screen yet */
    NW_MOVE_RIGHT(); NW_MOVE_RIGHT();

    /* since we ripped everything out, add screen move here */
    screenMoveRight();screenMoveRight();

    NW_DEL();

    screenDeleteChar(file->current->content);

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 0, "Screen cury should stay at 0");
    NW_ASSERT(screen.curx, 2, "Screen curx should be at 2");

    /**
     * @TODO add more tests here mixing screen movement, etc
     */
}

void
screenNewLineTest(file_t *file)
{
    NW_SCR_TEST();

    NW_MOVE_END();

    newLine(file);

    screenMoveEnd();
    screenNewLine(file->current->content);

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 1, "Screen cury is at 1");
    NW_ASSERT(screen.curx, 0, "Screen curx is at 0");
}

void
screenMoveEndTest(file_t *file)
{
    NW_SCR_TEST();

    screenMoveEnd();

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 0, "Screen cury remains 0");
    NW_ASSERT(screen.curx, 3, "Screen curx is 3");
}

void
screenMoveBegTest(file_t *file)
{
    NW_SCR_TEST();

    screenMoveRight();screenMoveRight();
    screenMoveBeg();

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 0, "Screen cury remains 0");
    NW_ASSERT(screen.curx, 0, "Screen curx is 0");
}

void
screenMoveRightTest(file_t *file)
{
    NW_SCR_TEST();

    screenMoveRight();
    screenMoveRight();

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 0, "Screen cury remains 0");
    NW_ASSERT(screen.curx, 2, "Screen curx is 2");
}

void
screenMoveLeftTest(file_t *file)
{
    NW_SCR_TEST();

    screenMoveEnd();
    screenMoveLeft();
    screenMoveLeft();

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 0, "Screen cury remains 0");
    NW_ASSERT(screen.curx, 1, "Screen curx is 1");
}

void
screenMoveDownTest(file_t *file)
{
    NW_SCR_TEST();

    screenMoveRight(); screenMoveRight();
    screenMoveDown(); screenMoveDown();

    getch();

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 2, "Screen cury is at 2");
    NW_ASSERT(screen.curx, 2, "Screen curx remains at 2");
}
