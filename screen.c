#include <ncurses.h>

#include "screen.h"

/**
 * @TODO this is 100% just stubbed out so we can get
 *       the brainstorming process going.
 */
void
initScreen()
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    printw("Coming Soon... The NW Editor!");
    refresh();
    getch();
    endwin();
}
