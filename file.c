#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"
#include "file.h"

/**
 * Load file's contents into a file_t struct. This can be used for serveral
 * different files as long as they're passed unique files. If the file exists
 * it will return true otherwise false
 */
void loadFile (file_t *file, char *fileName)
{
    file->name = fileName;
    file->totalLines = 0;
    file->lines = NULL;

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

            while (fgets(curLine, MAX_LINE_LENGTH, fp))
                {
                    head = malloc(sizeof(line_t));

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

                    file->totalLines++;
                    head->number = file->totalLines;
                    head->len    = strlen(curLine) - 1; /* Account for \n */
                    strcpy(head->content, curLine);

                    /* ptrs */
                    head->next = NULL;

                    last = head;
                    head = head->next;
                }

            fclose(fp);

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
}

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
void dumpFile (file_t file)
{
    printf("\n\nFILE NAME: %s\tLINES: %d\n", file.name, file.totalLines);
    printf("================================================\n\n");

    line_t *lines = file.lines;

    while (lines != NULL)
        {
            printf("LINE [%d][%d]\t\t%s", lines->number, lines->len, lines->content);
            lines = lines->next;
        }

    printf("\n\n");
}
