#include <stdio.h>
#include <stdlib.h>

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

            /**
             * @todo make this work with our freeNodes function
             */
            line_t *cur;
            line_t *next;

            cur = file.lines;

            while (cur->next != NULL)
                {
                    next = cur->next;
                    free(cur);
                    cur = next;
                }

            free(cur);
        }

    return 0;
}
