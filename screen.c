#include <ncurses.h>

#include "screen.h"

void initScreen(line_t *lines)
{
    initscr();
    getmaxyx(stdscr, screen.height, screen.width);
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    line_t *tmp;
    tmp = lines;

    while (tmp != NULL)
        {
            printw("%s", tmp->content);
            tmp = tmp->next;
        }

    move(0, 0);
    refresh();

    getch();
    endwin();
}
