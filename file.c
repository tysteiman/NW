#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"
#include "file.h"

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
            last = NULL;
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
                        }

                    file->totalLines++;
                    head->number = file->totalLines;
                    strcpy(head->content, curLine);

                    /* ptrs */
                    head->next = NULL;

                    last = head;
                    head = head->next;
                }

            fclose(fp);
        }
}
