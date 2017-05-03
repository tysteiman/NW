#include <stdlib.h>

#include "opt.h"
#include "file.h"
#include "screen.h"

int main(int argc, char **argv)
{
    if (argc > 1)
        {
            /**
             * At this point we only use getopt() as a way to set
             * variables. That being the case we can simply call
             * our parser which will get our application's options
             * ready to go.
             */
            parseOpts(argc, argv);

            file_t file;

            /**
             * Initialize the file based on filename. When the
             * file we're targeting doesn't exist we still get back
             * a built out line_t object with a single line.
             */
            loadFile(&file, opts.fileName);

            if (opts.debug)
                {
                    dumpFile(file);
                }
            else
                {
                    initScreen(file.lines);
                }

            /**
             * @TODO make this work with our freeNodes function
             */
            line_t *cur;
            line_t *next;

            cur = file.lines;

            /**
             * Free up our line_t nodes from memory. This needs
             * to be a little more agnostic and moved into a
             * good function that can clear any nodes passed
             * instead.
             */
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
