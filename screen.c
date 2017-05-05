#include <ncurses.h>
#include <string.h>

#include "screen.h"
#include "opt.h"

void initScreen(file_t *file)
{
    initscr();
    getmaxyx(stdscr, screen.height, screen.width);
    raw();
    keypad(stdscr, TRUE);
    noecho();

    line_t *tmp;
    tmp = file->lines;

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
            else if (!strcmp(input, "^N"))
                {
                    mvdown(file);
                }
            else
                {
                    printw("%c", ch);
                    refresh();
                }
        }
}

void mvdown(file_t *file)
{
    if (file->current->number != file->totalLines)
        {
            file->current = file->current->next;
            file->cursor.y++;
        }

    if (!opts.debug)
        {
            move(file->cursor.y, file->cursor.x);
        }
}
