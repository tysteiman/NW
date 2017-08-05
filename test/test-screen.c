#include "test-screen.h"
#include "test.h"

#include "../screen.h"

void
initScreenTestFile(file_t *file, char *fileName)
{
    clear();
    loadFile(file, fileName);
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
    screen.move_right();screen.move_right();

    NW_DEL();

    screenDeleteChar(file->current->content);

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 0, "Screen cury should stay at 0");
    NW_ASSERT(screen.curx, 2, "Screen curx should be at 2");
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

    screen.move_right();screen.move_right();
    screenMoveBeg();

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 0, "Screen cury remains 0");
    NW_ASSERT(screen.curx, 0, "Screen curx is 0");
}

void
screenMoveRightTest(file_t *file)
{
    NW_SCR_TEST();

    screen.move_right();screen.move_right();

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 0, "Screen cury remains 0");
    NW_ASSERT(screen.curx, 2, "Screen curx is 2");
}

void
screenMoveLeftTest(file_t *file)
{
    NW_SCR_TEST();

    screenMoveEnd();
    screen.move_left();
    screen.move_left();

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 0, "Screen cury remains 0");
    NW_ASSERT(screen.curx, 1, "Screen curx is 1");
}

void
screenMoveDownTest(file_t *file)
{
    NW_SCR_TEST();

    screen.move_right();
    screen.move_right();

    screen.move_down();
    screen.move_down();

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 2, "Screen cury is at 2");
    NW_ASSERT(screen.curx, 2, "Screen curx remains at 2");
}

void
screenInsertCharTest(file_t *file)
{
    /* insert after moving a bit */
    NW_SCR_TEST();

    NW_MOVE_END(); screenMoveEnd();
    NW_MOVE_DOWN(); screen.move_down();
    NW_MOVE_END(); screenMoveEnd();

    NW_INS(' '); screenInsertChar();
    NW_INS('!'); screenInsertChar();

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 1, "Screen cury at 1");
    NW_ASSERT(screen.curx, 11, "Screen curx at 11");

    /* insert at beginning of line */
    NW_SCR_TEST();

    NW_INS('z'); screenInsertChar();

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 0, "Screen cury still at 0");
    NW_ASSERT(screen.curx, 1, "Screen curx now at 1");
}

void
screenDeleteLineTest(file_t *file)
{
    NW_SCR_TEST();

    NW_MOVE_DOWN();NW_MOVE_DOWN();NW_MOVE_DOWN();
    NW_MOVE_DOWN();NW_MOVE_DOWN();NW_MOVE_DOWN();
    
    screen.move_down(); screen.move_down(); screen.move_down();
    screen.move_down(); screen.move_down(); screen.move_down();

    joinLine(file);
    screenDeleteLine();

    NW_SCR_CLOSE();

    NW_ASSERT(screen.cury, 5, "Screen cury at 5");
    NW_ASSERT(screen.curx, 3, "Screen curx at 3");
}
