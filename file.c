#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"
#include "file.h"
#include "screen.h"

/**
 * Load file's contents into a file_t struct. This can be used for serveral
 * different files as long as they're passed unique files. If the file exists
 * it will return true otherwise false
 */
void loadFile (file_t *file, char *fileName)
{
    file->name = fileName;
    file->totalLines = 0;
    file->edited = FALSE;
    file->lines = NULL;
    file->cursor.x = 0;
    file->cursor.y = 0;

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
                    strcpy(head->content, curLine);

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
void initializeEmptyNode(file_t *file)
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
void dumpFile (file_t *file)
{
    /**
     * Run any tests we may have for our files in debug mode.
     */
    executeFileTests(file);

    printf("\n\n\033[93mFILE NAME: %s\tLINES: %d\n", file->name, file->totalLines);
    printf("CURSOR POS (y:x): %d:%d\n", file->cursor.y, file->cursor.x);
    printf("CURRENT LINE: [%d]\t%s\n", file->current->number, file->current->content);
    printf("==================================================================\033[0m\n\n");

    line_t *lines = file->lines;

    while (lines != NULL)
        {
            printf("\033[93mLINE [%d][%d]\033[0m\t\t%s", lines->number, lines->len, lines->content);
            lines = lines->next;
        }

    printf("\n\n");
}

void executeFileTests(file_t *file)
{
    mvdown(file);
}
