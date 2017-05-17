#include <ncurses.h>
#include <string.h>

#include "screen.h"
#include "opt.h"
#include "file.h"

/**
 * Initialize our screen with ncurses and print our file. This
 * will also attach an event listener for handling key presses.
 * To avoid getting to this point and initializing curses, pass
 * the -d flag to our program.
 */
void
initScreen(file_t *file)
{
    /**
     * NCurses config / startup
     */
    initscr();
    getmaxyx(stdscr, screen.height, screen.width);
    raw();
    scrollok(stdscr, TRUE);
    keypad(stdscr, TRUE);
    noecho();

    line_t *tmp;
    tmp = file->lines;

    /**
     * Print our file's contents to our ncurses window only
     * until we run out of room. I'm not sure if this is the
     * default ncurses behavior but we want to not waste
     * resources trying to print the entire file.
     */
    while (tmp != NULL && tmp->number != screen.height)
        {
            printw("%s\n", tmp->content);
            tmp = tmp->next;
        }

    printStatusLine(file);

    /**
     * Place our cursor at the top left of our file ready
     * for navigation.
     */
    move(0, 0);
    refresh();

    attachKeyListener(file);
}

/**
 * Attach keys to our screen functions by parsing keyname(getch()). This
 * essentially starts a REPL that we sit on until the user presses CTRL + Q.
 */
void
attachKeyListener(file_t *file)
{
    while (1)
        {
            char *input;
            char ch = getch();

            /**
             * The actual string value / key name of our input via getch()
             */
            input = keyname(ch);

            /**
             * CTRL + Q : Exit program
             */
            if (!strcmp(input, "^Q"))
                {
                    endwin();
                    break;
                }
            /**
             * CTRL + S : Save File
             */
            else if (!strcmp(input, "^S"))
                {
                    saveFile(file);

                    /**
                     * @TODO here we need to update the status bar once we have one
                     *       that would ultimately set the status as not edited and
                     *       perhaps a message saying the file has been saved.
                     */
                }
            /**
             * CTRL + N : Move down 1 line
             */
            else if (!strcmp(input, "^N"))
                {
                    mvdown(file);
                }
            /**
             * CTRL + P : Move up 1 line
             */
            else if (!strcmp(input, "^P"))
                {
                    mvup(file);
                }
            /**
             * CTRL + F : Move right 1 char or to
             * the beginning of the next line if starting
             * at the end of the line
             */
            else if (!strcmp(input, "^F"))
                {
                    mvright(file);
                }
            /**
             * CTRL + E : Move to end of current line
             */
            else if (!strcmp(input, "^E"))
                {
                    mvendofln(file, TRUE);
                }
            /**
             * CTRL + B : Move left 1 char or end of
             * previous line if starting at beginning
             * of line.
             */
            else if (!strcmp(input, "^B"))
                {
                    mvleft(file);
                }
            /**
             * CTRL + A : Move to beginning of current line
             */
            else if (!strcmp(input, "^A"))
                {
                    mvbegofline(file, TRUE);
                }
            /**
             * Handle text input by dumping the char into
             * the buffer.
             * @TODO this should be updated so that only
             * accepted chars are entered to the buffer. For
             * example control characters "^C" etc are being
             * entered into the buffer. Allow anything except
             * for those control chars.
             */
            else
                {
                    /**
                     * Divert to our input handler so we keep this
                     * ugly endless if statement readable.
                     */
                    handleInput(ch, input, file);
                }
        }
}

/**
 * Handle non-registered key input. As long as the input is not a
 * control character we can assume we should just dump it into the
 * buffer as 'code' or text. This is done by simply determining where
 * we are in relation to the current line and moving from there.
 */
void
handleInput(char ch, char *input, file_t *file)
{
    int atEnd;
    
    atEnd = file->cursor.x == file->current->len ? TRUE : FALSE;

    if (ch == '\n')
        {
            /**
             * At this point we should be completely set up with a new
             * line set on file->current we just need to update the
             * screen to shift the lines down and move the physical cur
             */
            if (atEnd)
                {
                    newLine(file);
                    /**
                     * @TODO when we get to this point we basiclly clone
                     * the line virtually but not in the actual file. on Mac
                     * terminal it is blowing up however on linux it seems to
                     * work for whatever reason. Maybe we need to try something
                     * else in terms of display like clearning the line, not sure.
                     */
                    shiftLinesDown(file);
                }

            printStatusLine(file);
        }

    /* CURSOR.X AT THE END OF LINE */
    else if (atEnd)
        {
            file->current->content[file->cursor.x] = ch;
            printw("%c", ch);
            file->current->len++;
            file->cursor.x++;
            file->cursor.xSnap = file->cursor.x;
        }

    refresh();

    /**
     * @TODO we will eventually handle the text properly but for
     * now assume the file is 'edited'
     */
    file->edited = TRUE;
}

void
shiftLinesDown(file_t *file)
{
    printw("\n");
    line_t *line;

    line = file->current;

    while (line != NULL)
        {
            printw("%s\n", line->content);
            line = line->next;
        }

    move(file->cursor.y, file->cursor.x);
    refresh();
}

void
mvdown(file_t *file)
{
    if (file->current->number != file->totalLines)
        {
            file->current = file->current->next;
            file->cursor.y++;

            snaptoend(file);
            /**
             * @TODO instead of hard coding this routines we need to
             * add a layer of abstraction for similar commands like
             * mvup & mvdown so that we can kind of 'hook' into
             * these functions and run in this case snaptoend()
             * and printstatusline() after these core functions, followed
             * by the the move() calls.
             */
            printStatusLine(file);
        }

    if (!opts.debug)
        {
            move(file->cursor.y, file->cursor.x);
        }
}

void
mvup(file_t *file)
{
    if (file->current->number != 1)
        {
            file->current = file->current->prev;
            file->cursor.y--;

            snaptoend(file);
            printStatusLine(file);
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
 */
void
snaptoend(file_t *file)
{
    if ( file->cursor.x > file->current->len ||
         file->cursor.xSnap > file->current->len )
        {
            mvendofln(file, FALSE);
        }
    else
        {
            file->cursor.x = file->cursor.xSnap;
            move(file->cursor.y, file->cursor.x);
        }
}

void
mvright(file_t *file)
{
    int mv;
    mv = TRUE;

    if (file->cursor.x != file->current->len)
        {
            file->cursor.x++;
            file->cursor.xSnap = file->cursor.x;
        }
    else
        {
            mvdown(file);
            mvbegofline(file, FALSE);
            mv = FALSE;
        }

    if (!opts.debug && mv)
        {
            move(file->cursor.y, file->cursor.x);
        }
}

void
mvendofln(file_t *file, int mv)
{
    if (file->cursor.x != file->current->len)
        {
            file->cursor.x = file->current->len;

            if (mv)
                {
                    file->cursor.xSnap = file->cursor.x;
                }
        }

    if (!opts.debug)
        {
            move(file->cursor.y, file->current->len);
        }
}

void
mvbegofline(file_t *file, int mv)
{
    if (file->cursor.x != 0)
        {
            file->cursor.x = 0;

            if (mv)
                {
                    file->cursor.xSnap = 0;
                }
        }

    if (!opts.debug)
        {
            move(file->cursor.y, 0);
        }
}

void
mvleft(file_t *file)
{
    int mv;
    mv = TRUE;

    if (file->cursor.x != 0)
        {
            file->cursor.x--;
            file->cursor.xSnap = file->cursor.x;
        }
    else
        {
            mvup(file);
            mvendofln(file, FALSE);
            mv = FALSE;
        }

    if (!opts.debug && mv)
        {
            move(file->cursor.y, file->cursor.x);
        }
}

void
printStatusLine(file_t * file)
{
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    mvprintw(screen.height - 1, 0, "%s : %d\t", opts.fileSaveTarget, file->current->number);

    attroff(COLOR_PAIR(2));

    move(file->cursor.y, file->cursor.x);
}
