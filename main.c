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
#include <string.h>

#include "lib.h"
#include "flags.h"
#include "file.h"

int main(int argc, char **argv)
{
    if (argc > 1) {
        char *fileName;
        file_t file;

        file.name = argv[1];
        file.totalLines = 0;
        file.lines = NULL;

        if (fileExists(file.name)) {
            FILE *fp;
            fp = fopen(file.name, "r");

            if (!fp) {
                err("Unable to open file.");
            }

            file.lines = malloc(sizeof(line_t));

            while (fgets(file.lines->content, MAX_LINE_LENGTH, fp)) {
                ++file.totalLines;
                file.lines->number = file.totalLines;
                file.lines->len    = strlen(file.lines->content) - 1; /* Account for \n */
            }

            free(file.lines);

            fclose(fp);
        }
    }

    return 0;
}
