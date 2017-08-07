#include <ncurses.h>

#include "screen.h"

/**
 * Dump our file's contents onto our screen. This should be the only
 * front end function we're not really worried about because we really just
 * want to get the text loaded on the screen, and standing by for user input.
 * After that point we need to dispatch the commands between backend and frontend.
 */
void
initScreen(file_t *file)
{
    screen.move_left = screenMoveLeft;
    screen.move_right = screenMoveRight;
    screen.move_up = screenMoveUp;
    screen.move_down = screenMoveDown;
    screen.move_end = screenMoveEnd;
    screen.move_beg = screenMoveBeg;
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    getmaxyx(stdscr, screen.maxy, screen.maxx);

    line_t *head = file->current;

    NW_PRINT(file->current);

    screen.cury = 0;
    screen.curx = 0;

    NW_MOVE_TO_CUR();

    refresh();
}

void
printLines(line_t *head, int totalLines)
{
    int scrcury = screen.cury;
    while(head != NULL && NW_CURY != screen.maxy)
        {
            printw("%s\n", head->content);
            head = head->next;
            ++screen.cury;
        }
    screen.cury = scrcury;
    refresh();
}

void
resizeScreen(file_t *file)
{
    clear();
    getmaxyx(stdscr, screen.maxy, screen.maxx);
    NW_PRINT(file->current);

    screen.cury = 0;
    screen.curx = 0;

    NW_CUR_SYNC();
}

void
screenDeleteChar(char *cur)
{
    printLine(cur);
}

void
printLine(char *cur)
{
    move(screen.cury, 0);
    clrtoeol();
    printw("%s\n", cur);
    refresh();
    move(screen.cury, screen.curx);
}

void
screenInsertChar()
{
    printLine(file.current->content);
    ++screen.curx;
    NW_MOVE_TO_CUR();
}

void
screenMoveRight()
{
    ++screen.curx;

    NW_MOVE_TO_CUR();
}

void
screenMoveLeft()
{
    --screen.curx;
    
    NW_MOVE_TO_CUR();
}

void
moveToCursor()
{
    move(screen.cury, screen.curx);
    refresh();
}

void
screenNewLine(char *cur)
{
    printLines(file.current->prev, file.totalLines);
    ++screen.cury;
    NW_MOVE_TO_CUR();
}

void
screenMoveEnd()
{
    screen.curx = file.current->len;
    NW_MOVE_TO_CUR();
}

void
screenMoveBeg()
{
    screen.curx = 0;
    NW_MOVE_TO_CUR();
}

void
screenMoveDown()
{
    ++NW_CURY;
    NW_MOVE_TO_CUR();
}

void
screenMoveUp()
{
    if (NW_CURY != 0)
        {
            --NW_CURY;
            NW_MOVE_TO_CUR();
        }
}

void
screenDeleteLine()
{
    if (NW_CURY != 0)
        {
            clrtobot();
            printLines(file.current->next, file.totalLines);
            --NW_CURY;
            NW_CURX = file.current->len;
            NW_MOVE_TO_CUR();
        }
}

void
screenScrollDown(file_t *file)
{
    clear();
    NW_MOVE_DOWN();
    NW_CURY = 0;
    NW_PRINT(CURRENT);
    NW_MOVE_TO_CUR();
}

void
screenScrollUp(line_t *head)
{
    int curx = NW_CURX;
    clear();

    NW_CURY = NW_MAXY;

    while (NW_CURY != 0)
        {
            head = head->prev;
            --NW_CURY;
        }

    printLines(head, file.totalLines);

    NW_CURY = NW_MAXY;
    NW_MOVE_TO_CUR();

    refresh();
}
