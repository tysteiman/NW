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
