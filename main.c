#include <stdio.h>

#include "file.h"

int main(int argc, char **argv)
{
    if (argc > 1)
        {
            char *fileName;
            file_t file;

            fileName = argv[1];

            loadFile(&file, fileName);

            dumpFile(file);
        }
    return 0;
}
