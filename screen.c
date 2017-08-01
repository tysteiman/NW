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

/**
 * @TODO for these types of routines we are NOT worried about actually setting
 *       the cursor position to a T, it should actually work off the file/line
 *       routines as a dispatch or almost 'ok update the cursor'. In this case
 *       all we need to do is repaint the line and put the cursor back to where
 *       it was in the first place. In Vim/Nano the curpos is not updated when
 *       you delete a single char (this function's purpose)
 * @TODO this should actually work for screenInsertChar as well... I think the
 *       only difference is moving curx in the process 1.
 */
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
screenMoveRight()
{
    /**
     * @NOTE as of right now the whole purpose of this is to follow the line's
     *       activity as much as possible and invoke this function from within
     *       the backend system in order to keep things from getting confusing.
     *       in other words we can run through a bunch of logic and scenarios,
     *       update the cursor value and simply 'ping' the front end to move
     * @TODO for more advanced scenarios should we be tracking some kind of value
     *       so we can just call move? I want to keep ALL screen stuff out of
     *       the backend except for ONE invocation at the end if possible!
     */
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
