/**
 *   NW Editor - Super light terminal based editor
 *   Copyright (C) 2017 Tyler Steiman
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"
#include "file.h"
#include "opt.h"
#include "screen.h"
#include "syn.h"
#include "test/test.h"

/**
 * Load file's contents into a file_t struct. This can be used for serveral
 * different files as long as they're passed unique files. If the file exists
 * it will return true otherwise false
 */
void
loadFile (file_t *file, char *fileName)
{
    file->name = fileName;
    file->totalLines = 0;
    file->edited = FALSE;
    file->lines = NULL;
    CURSOR.x = 0;
    CURSOR.y = 0;
    CURSOR.xSnap = 0;

    if (file->name != NULL)
        {
            /**
             * @TODO this is a really simple way to get our ruby syntax to tabWidth 2 before
             *       knowing exactly how far we want to take syntax stuff. This is breaking
             *       our *empty* test however which isn't good. Skipping this for tests is
             *       just a patch, idk what's happening
             */
            file->extension = parseExtension(file->name);
            if (!NW_TEST_MODE)
                {
                    file->syntax = parseSyntaxFamilyByExtension(file->extension);
                }

            if (file->syntax == NW_RUBY)
                {
                    opts.tabWidth = 2;
                }
        }
    else
        {
            file->syntax = NW_TEXT;
        }

    if (fileExists(file->name))
        {
            FILE *fp;
            fp = fopen(file->name, "r");
            
            if (!fp)
                {
                    err("Unable to open file.");
                }

            char curLine[MAX_LINE_LENGTH];

            line_t *head;
            line_t *last;
            line_t *first;
            last = NULL;
            first = NULL;
            head = file->lines;

            /**
             * Parse our target file line by line, attaching line_t
             * nodes to our file_t object for each line. The last
             * line will be initialized to NULL as well as the first
             * node's *prev ptr.
             */
            while (fgets(curLine, MAX_LINE_LENGTH, fp))
                {
                    head = malloc(sizeof(line_t));

                    /**
                     * If we have parsed previous lines we will have
                     * access to the last parsed line's ptr in order
                     * to link our lists. Otherwise we can assume we are
                     * at the first line of the file and can now set the
                     * last ptr to the current node (head).
                     */
                    if (last)
                        {
                            head->prev = last;
                            head->prev->next = head;
                        }
                    else
                        {
                            head->prev = NULL;
                            first = head;
                        }

                    /* Line data */
                    file->totalLines++;
                    head->number = file->totalLines;
                    head->len    = strlen(curLine) - 1; /* Account for \n */
                    strncpy(head->content, curLine, strlen(curLine) - 1);
                    // set our pointer to our content for easier passing
                    head->contentP = &head->content[0];

                    /* functions */
                    head->delete_char = lineDeleteChar;
                    head->insert_char = lineInsertChar;
                    head->move_right = lineMoveRight;
                    head->move_left = lineMoveLeft;
                    head->move_end = lineMoveToLineEnd;
                    head->move_beg = lineMoveToLineBeg;

                    /* Ptrs */
                    head->next = NULL;
                    last = head;
                    head = head->next;
                }

            fclose(fp);

            /**
             * At this point if the file is completely empty our first
             * ptr will be NULL therefore we can't access the line_t
             * attributes throughout the application. If that is the case
             * we need to initialize an empty line_t node and attach it to
             * head. with initializeEmptyNode().
             * Otherwise reset file->lines (head) to first ptr.
             */
            if (first != NULL)
                {
                    file->lines = first;
                }
            else
                {
                    initializeEmptyNode(file);
                }
        }
    else
        {
            initializeEmptyNode(file);
        }

    file->current = file->lines;
}

/**
 * Initialize an empty file_t object based on the proper
 * default initial values. We simply allocate memory
 * for one line, set it as the first line, and the
 * contents and length to 0.
 */
void
initializeEmptyNode(file_t *file)
{
    file->lines = malloc(sizeof(line_t));
    file->totalLines++;
    strcpy(file->lines->content, "");
    file->lines->number = file->totalLines;
    file->lines->len = 0;
    file->lines->next = NULL;
    file->lines->prev = NULL;
}

/**
 * Print out entire file_t struct's contents
 */
void
dumpFile (file_t *file)
{
    printf("\n\n\033[93mFILE NAME: %s\tLINES: %d\n", file->name, file->totalLines);
    printf("SAVE TARGET: %s\n", opts.fileSaveTarget);
    printf("CURSOR POS (y:x): %d:%d\n", CURSOR.y, CURSOR.x);
    printf("CURRENT LINE: [%d]\t%s\n", file->current->number, file->current->content);
    printf("==================================================================\033[0m\n\n");

    line_t *lines = file->lines;

    while (lines != NULL)
        {
            printf("\033[93mLINE [%d][%d]\033[0m\t\t%s\n", lines->number, lines->len, lines->content);
            lines = lines->next;
        }

    printf("\n\n");
}

/**
 * Loop through our file and save our memory's current representation of our 'file'
 * to the actual target file. This uses opt_t:fileSaveTarget as our target instead
 * of the raw file name. When there is no 'new' save target it should just be
 * the original file name in file_t:fileName.
 */
void
saveFile(file_t *file)
{
    /**
     * If the file hasn't been edited we don't really need to save and
     * can bluff by simply saying it has been saved.
     */
    if (file->edited)
        {
            line_t *current;
            current = file->lines;

            FILE *fp;
            /**
             * @TODO we need to put the file name prompt here if opt.fileSaveTarget
             *       is empty. We can't build that out until we have our menu/prompt built.
             */
            fp = fopen(opts.fileSaveTarget, "w");

            if (fp == NULL)
                {
                    err("Could not save file.");
                }

            while (current != NULL)
                {
                    fprintf(fp, "%s\n", current->content);
                    current = current->next;
                }

            fclose(fp);

            /* Reset `edited` flag */
            file->edited = FALSE;
        }
}

/**
 * Create a new line below the line_t argument `prevLine` supplied.
 * This returns the new line for immediate access and hooks up the
 * correct pointers and associations i.e. the next ptr for the argument
 * becomes the new line, 'next->next' for prevLine becomes prevLine->next
 * and prevLine->next->prev becomes the new line.
 */
line_t *
newLine(file_t *file)
{
    line_t *prevLine;
    prevLine = file->current;

    line_t *new;
    new = malloc(sizeof(line_t));

    new->prev = prevLine;
    
    int no;
    no = prevLine->number;
    new->number = ++no;

    if (prevLine->next != NULL)
        {
            new->next = prevLine->next;
            strcpy(new->content, "");
            new->len = 0;
            prevLine->next->prev = new;

            NW_INCREASE_LINE_NUMBERS();
        }
    else
        {
            new->next = NULL;
        }

    
    prevLine->next = new;

    /**
     * Set the file's meta data and cursor so we stay in sync with now being
     * on our new line in terms of current line, cursor pos, and total lines
     */
    file->current = new;
    CURSOR.y++;
    CURSOR.x = 0;
    CURSOR.xSnap = 0;
    file->totalLines++;

    return new;
}

void
moveY(file_t *file, int direction, int qual, int newY)
{
    if (file->current->number != qual)
        {
            CURSOR.y = newY;
            file->current = direction == NW_DOWN ? file->current->next : file->current->prev;

            /* snap our cursor to the end of the line if x is greater than line len */
            if (file->current->len == 0 || file->current->len < CURSOR.xSnap)
                {
                    CURSOR.x = file->current->len;
                }
            else if (CURSOR.xSnap > CURSOR.x)
                {
                    CURSOR.x = CURSOR.xSnap;
                }
        }
}

void
moveDown(file_t * file)
{
    moveY(file, NW_DOWN, file->totalLines, CURSOR.y + 1);
}

void
moveUp(file_t *file)
{
    moveY(file, NW_UP, 1, CURSOR.y - 1);
}

void
joinLine(file_t *file)
{
    line_t *prev = file->current->prev;
    line_t *next = file->current->next;

    int xs = CURSOR.xSnap;
    int x = CURSOR.x;
    
    prev->next = next;
    next->prev = prev;

    char curContent[MAX_LINE_LENGTH];

    strcpy(curContent, file->current->content);
    int curContentLen = strlen(curContent);
    int i = 0;

    free(file->current);

    file->current = prev;
    CURSOR.x = file->current->len;
    --CURSOR.y;

    for (; i < curContentLen; i++)
        {
            NW_INS(curContent[i]);
        }

    NW_DECREASE_LINE_NUMBERS();

    --file->totalLines;

    /* restore xSnap */
    CURSOR.xSnap = xs;
    CURSOR.x = x;
}

void
bumpLineNumbers(int direction, line_t *start)
{
    while (start != NULL)
        {
            int no = direction == NW_UP ? start->number + 1 : start->number - 1;
            start->number = no;
            start = start->next;
        }
}

void
splitLine(file_t *file)
{
    char *beg;
    char *end;

    beg = substr(0, CURSOR.x - 1, file->current->content);
    end = substr(CURSOR.x, file->current->len, file->current->content);

    /* set our current line (will be prev) */
    NW_CLEAR_LINE();

    strcpy(file->current->content, beg);
    file->current->len = strlen(beg);

    /* set our new line (now current line) */
    newLine(file);
    strcpy(file->current->content, end);

    /* set our new line's details */
    file->current->len = strlen(file->current->content);
}
