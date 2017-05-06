#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "opt.h"
#include "lib.h"

void parseOpts(int argc, char **argv)
{
    int curOpt;

    while ((curOpt = getopt(argc, argv, "d?f:")) != -1)
        {
            switch (curOpt)
                {
                case 'd':
                    opts.debug = TRUE;
                    break;
                case '?':
                    fprintf(stderr, "USAGE: nw [-option] <file_name>\n");
                    break;
                    exit(EXIT_SUCCESS);
                case 'f':
                    opts.fileSaveTarget = optarg;
                    break;
                default:
                    err("Invalid argument.");
                }
        }

    opts.fileName = argv[optind];

    if (!opts.fileSaveTarget)
        {
            opts.fileSaveTarget = opts.fileName;
        }
}
