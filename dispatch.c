#include "dispatch.h"
#include "screen.h"

void
dispatchRight(file_t *file)
{
    if (NW_CURX != file->current->len)
        {
            NW_MOVE_RIGHT();
            screen.move_right();
        }
}

void
dispatchLeft(file_t *file)
{
    if (NW_CURX != 0)
        {
            NW_MOVE_LEFT();
            screen.move_left();
        }
}

void
dispatchEnd(file_t *file)
{
    NW_MOVE_END();
    screen.move_end();
}

void
dispatchBeg(file_t *file)
{
    NW_MOVE_BEG();
    screen.move_beg();
}

void
dispatchInsert(char c, file_t *file)
{
    NW_INS(c);
    screenInsertChar();
}
