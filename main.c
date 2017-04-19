/**
 * @todo create new library for file functions. in order to do this
 * we will need to know how structs will be broken down in terms
 * of window, pointer, etc. i'm thinking a window should hold
 * structs like pointer (x, y) and file (name, lines (struct)).
 * Line should hold length, number, before & next pointers
 * assumingly. the back end of that functionality can be completely
 * build in terms of loading the structs with data. after that
 * a testing suite of some sort needs to be built before performing
 * text manipulation operations.
 *
 * @todo we need initialization functions for the structures.
 * the structs can get built off off and returned as needed
 * depending on whether it's a new file or loading a file.
 * simple flags should be able to be passed for that.
 *
 * @todo make library for handling linked lists. we will probably
 * end up with a couple so it's important we can create a library
 * and use the same functions with all linked lists.
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "lib.h"
#include "flags.h"
#include "file.h"

int main(int argc, char **argv)
{
    char *fileName;

    while ((curFlag = getopt(argc, argv, "t")) != -1) {
        switch (curFlag) {
        case 't':
            terminalFlag = TRUE;
            break;
        default:
            err("Argument Error");
        }
    }

    /* Get our file name from unused opt value */
    fileName = argv[optind];

    if (fileName && fileExists(fileName)) {
        file_t file = loadFile(fileName);
    } else {
        if (terminalFlag) {
            /**
             * We have no terminal actions to be done here since we are
             * creating a new file.
             */
            printf("Terminal mode enabled for new file (%s) -- nothing to do.\n", fileName);
        } else {
            file_t file = newFile(fileName);
        }
    }

    return 0;
}
