#include <ncurses.h>

#include "screen.h"

/**
 * Dump our file's contents onto our screen. This should be the only
 * front end function we're not really worried about because we really just
 * want to get the text loaded on the screen, and standing by for user input.
 * After that point we need to dispatch the commands between backend and frontend.
 * @TODO think about breaking down printing the file's contents into a function
 *       since I think we will need to use that when repainting content.
 */
void
initScreen(file_t *file)
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    getmaxyx(stdscr, screen.maxy, screen.maxx);

    line_t *head = file->current;

    NW_PRINT(file->current);

    screen.cury = 0;

    NW_CUR_SYNC();

    refresh();
}

void
printLines(line_t *head, int totalLines)
{
    while(head != NULL && head->number != totalLines && screen.cury != screen.maxy)
        {
            printw("%s\n", head->content);
            head = head->next;
            ++screen.cury;
        }
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
screenDeleteChar(line_t *cur)
{
    move(screen.cury, 0);
    clrtoeol();
    printw("%s\n", cur->content);
    refresh();
    move(screen.cury, screen.curx);
}
