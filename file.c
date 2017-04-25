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

        while (fgets(curLine, MAX_LINE_LENGTH, fp))
        {
            printf("LINE: %s", curLine);
        }

        fclose(fp);
    }
}
