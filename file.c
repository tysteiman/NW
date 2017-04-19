#include <stdio.h>
#include "file.h"

file_t loadFile(char *fileName)
{
    printf("LOAD FILE FUNCTION: %s\n", fileName);
    file_t file = newFile(fileName);

    return file;
}

file_t newFile(char *fileName)
{
    printf("NEW FILE FUNCTION: %s\n", fileName);
    file_t file;

    file.name       = fileName;
    file.totalLines = 0;

    return file;
}
