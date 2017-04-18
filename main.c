#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "lib.h"
#include "flags.h"

int main(int argc, char **argv)
{
    char *file;

    while ((curFlag = getopt(argc, argv, "t")) != -1) {
        switch (curFlag) {
        case 't':
            terminalFlag = TRUE;
            break;
        default:
            err("Argument Error");
        }
    }

    file = argv[optind];

    if (file && fileExists(file)) {
        printf("open file: %s\n", file);
    } else {
        if (terminalFlag) {
            printf("Terminal mode enabled for new file (%s) -- nothing to do.\n", file);
        } else {
            printf("create new file: %s\n", file);
        }
    }

    return 0;
}
