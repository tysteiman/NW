#include <ncurses.h>

#include "screen.h"

/**
 * @TODO this is 100% just stubbed out so we can get
 *       the brainstorming process going.
 */
void
initScreen(file_t *file)
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    getmaxyx(stdscr, screen.maxy, screen.maxx);

    line_t *head = file->current;

    while(head != NULL && head->number != file->totalLines && head->number != screen.maxy )
        {
            printw("%s\n", head->content);
            head = head->next;
        }

    /* @TODO we should not do this */
    move(0, 0);

    refresh();
    getch();
    endwin();
}
