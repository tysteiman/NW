#include <stdio.h>
#include <stdlib.h>

#include "lib.h"
#include "file.h"

file_t loadFile(char *fileName)
{
    file_t file = newFile(fileName);

    return file;
}

file_t newFile(char *fileName)
{
    file_t file;

    file.name       = fileName;
    file.totalLines = 0;

    return file;
}
