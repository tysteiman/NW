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
    while(head != NULL && head->number != totalLines && screen.cury != screen.maxy)
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
    ++screen.cury;
    NW_MOVE_TO_CUR();
}

void
screenMoveUp()
{
    if (screen.cury != 0)
        {
            --screen.cury;
            NW_MOVE_TO_CUR();
        }
}

void
screenDeleteLine()
{
    if (screen.cury != 0)
        {
            printLines(file.current->next, file.totalLines);
            --screen.cury;
            screen.curx = file.current->len;
            NW_MOVE_TO_CUR();
        }
}
