#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "file.h"

int main(int argc, char **argv)
{
    int debug;
    char *fileName;

    debug = FALSE;

    if (argc > 1)
        {
            int curOpt;

            while ((curOpt = getopt(argc, argv, "d?")) != -1)
                {
                    switch (curOpt)
                        {
                        case 'd':
                            debug = TRUE;
                            break;
                        case '?':
                            fprintf(stderr, "USAGE: nw [-option] <file_name>\n");
                            exit(EXIT_SUCCESS);
                        default:
                            err("Invalid argument.");
                        }
                }

            fileName = argv[optind];

            file_t file;

            loadFile(&file, fileName);

            if (debug) {
                dumpFile(file);
            }

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
