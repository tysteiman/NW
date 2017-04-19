#include <stdio.h>
#include "file.h"

void loadFile(char *fileName)
{
    printf("LOAD FILE FUNCTION: %s\n", fileName);
}

file_t newFile(char *fileName)
{
    file_t file;

    file.name       = fileName;
    file.totalLines = 0;

    return file;
}
