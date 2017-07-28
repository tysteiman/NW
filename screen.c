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
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    getmaxyx(stdscr, screen.maxy, screen.maxx);

    line_t *head = file->current;

    /**
     * @TODO break this out into a helper function that takes the screen.curx instead of
     *       of head->number which only works since we're initializing the screen. If
     *       we get lazy with front end stuff it's going to be a disaster.
     */
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
