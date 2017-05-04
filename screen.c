#include <ncurses.h>
#include <string.h>

#include "screen.h"

void initScreen(line_t *lines)
{
    initscr();
    getmaxyx(stdscr, screen.height, screen.width);
    raw();
    keypad(stdscr, TRUE);
    noecho();

    line_t *tmp;
    tmp = lines;

    while (tmp != NULL && tmp->number != screen.height)
        {
            printw("%s", tmp->content);
            tmp = tmp->next;
        }

    /**
     * @TODO this end tag serves as a placeholder for where
     * our status bar can go! that will only need to be one line
     * and can hopefully be swapped out without doing a bunch
     * of horse trash on the side.
     */
    printw("<end>\n");

    move(0, 0);
    refresh();

    while (1)
        {
            char *input;
            char ch = getch();

            input = keyname(ch);

            if (!strcmp(input, "^Q"))
                {
                    endwin();
                    break;
                }
            else
                {
                    printw("%c", ch);
                    refresh();
                }
        }
}
