#include <stdlib.h>

#include "opt.h"
#include "file.h"
#include "screen.h"
#include "dispatch.h"
#include "test/test.h"

int
main(int argc, char **argv)
{
    char *fileName;

    if (argc > 1)
        {
            /**
             * At this point we only use getopt() as a way to set
             * variables. That being the case we can simply call
             * our parser which will get our application's options
             * ready to go.
             */
            parseOpts(argc, argv);
            fileName = opts.fileName;
        }

    /**
     * Initialize the file based on filename. When the
     * file we're targeting doesn't exist we still get back
     * a built out line_t object with a single line.
     */
    loadFile(&file, opts.fileName);
    
    /**
     * Run test suite if prompted
     */
    if (opts.test)
        {
            testFile(&file);
        }
    else
        {
            NW_SCR_INIT();

            while (1)
                {
                    int input = getch();
                    char *name = keyname(input);

                    NW_CUR();

                    /* resize terminal */
                    if (input == KEY_RESIZE)
                        {
                            resizeScreen(&file);
                            continue;
                        }
                        
                    else if (NW_KEY_EQ(NW_NEW_LINE))
                        {
                            dispatchNewLine(&file);
                            continue;
                        }

                    else if (NW_KEY_EQ(NW_KEY_RIGHT))
                        {
                            dispatchRight(&file);
                            continue;
                        }

                    else if (NW_KEY_EQ(NW_KEY_LEFT))
                        {
                            dispatchLeft(&file);
                            continue;
                        }

                    else if (NW_KEY_EQ(NW_KEY_END))
                        {
                            dispatchEnd(&file);
                            continue;
                        }

                    else if (NW_KEY_EQ(NW_KEY_BEG))
                        {
                            dispatchBeg(&file);
                            continue;
                        }

                    /* exit screen */
                    else if (NW_KEY_EQ(NW_KEY_EXIT))
                        {
                            NW_SCR_CLOSE();
                            break;
                        }

                    else if (NW_KEY_EQ(NW_KEY_SAVE))
                        {
                            file.edited = TRUE;
                            saveFile(&file);
                            continue;
                        }

                    else if (NW_KEY_EQ(NW_KEY_DEL))
                        {
                            dispatchDeleteChar(&file);
                            continue;
                        }

                    else if (NW_KEY_EQ(NW_KEY_DOWN))
                        {
                            dispatchDown(&file);
                            continue;
                        }

                    else if (NW_KEY_EQ(NW_KEY_UP))
                        {
                            dispatchUp(&file);
                            continue;
                        }
                    else
                        {
                            dispatchInsert(input, &file);
                        }
                }
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

    return 0;
}
