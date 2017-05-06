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
            else if (!strcmp(input, "^P"))
                {
                    mvup(file);
                }
            else if (!strcmp(input, "^F"))
                {
                    mvright(file);
                }
            else if (!strcmp(input, "^E"))
                {
                    mvendofln(file);
                }
            else if (!strcmp(input, "^B"))
                {
                    mvleft(file);
                }
            else if (!strcmp(input, "^A"))
                {
                    mvbegofline(file);
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

            snaptoend(file);
        }

    if (!opts.debug)
        {
            move(file->cursor.y, file->cursor.x);
        }
}

void mvup(file_t *file)
{
    if (file->current->number != 1)
        {
            file->current = file->current->prev;
            file->cursor.y--;

            snaptoend(file);
        }

    if (!opts.debug)
        {
            move(file->cursor.y, file->cursor.x);
        }
}

/**
 * Snap cursor pos to end of line depending on current position.
 * This is used when navigating up and down lines that are different
 * lengths.
 * @TODO we need to add some kind of a counter or way to keep tabs
 * on the current x value to snap back to. For example, when starting
 * on a line that has 15 characters, navigating down one line that only
 * has 2 lines, then navigating down again to one with 30, it should
 * snap back to x:15 in order to fluidly scroll down the file without
 * crazily snapping down columns and back up.
 */
void snaptoend(file_t *file)
{
    if (file->cursor.x > file->current->len)
        {
            mvendofln(file);
        }
}

void mvright(file_t *file)
{
    int mv;
    mv = TRUE;

    if (file->cursor.x != file->current->len)
        {
            file->cursor.x++;
        }
    else
        {
            mvdown(file);
            mvbegofline(file);
            mv = FALSE;
        }

    if (!opts.debug && mv)
        {
            move(file->cursor.y, file->cursor.x);
        }
}

void mvendofln(file_t *file)
{
    if (file->cursor.x != file->current->len)
        {
            file->cursor.x = file->current->len;
        }

    if (!opts.debug)
        {
            move(file->cursor.y, file->current->len);
        }
}

void mvleft(file_t *file)
{
    int mv;
    mv = TRUE;

    if (file->cursor.x != 0)
        {
            file->cursor.x--;
        }
    else
        {
            mvup(file);
            mvendofln(file);
            mv = FALSE;
        }

    if (!opts.debug && mv)
        {
            move(file->cursor.y, file->cursor.x);
        }
}

void mvbegofline(file_t *file)
{
    if (file->cursor.x != 0)
        {
            file->cursor.x = 0;
        }

    if (!opts.debug)
        {
            move(file->cursor.y, 0);
        }
}
