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
                        
                    else if (NW_KEY_EQ(NW_KEY_NEW_LINE))
                        {
                            file.edited = TRUE;
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
                            saveFile(&file);
                            continue;
                        }

                    else if (NW_KEY_EQ(NW_KEY_DEL))
                        {
                            file.edited = TRUE;
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

                    else if (NW_KEY_EQ(NW_KEY_DEL_LINE))
                        {
                            dispatchDeleteLine(&file);
                            continue;
                        }
                    else
                        {
                            /**
                             * @TODO at some point we need to make sure the user isn't
                             *       trying to close a file that's been edited and not
                             *       saved! we should be able to do that by simply checking
                             *       file.edited here.
                             */
                            file.edited = TRUE;
                            if (input == NW_KEY_RET)
                                {
                                    if (NW_CURX == file.current->len)
                                        {
                                            dispatchNewLine(&file);
                                        }
                                    else
                                        {
                                            dispatchSplitLine(&file);
                                        }
                                }
                            else
                                {
                                    dispatchInsert(input, &file);
                                }
                        }
                }
        }
    freeNodes(file.lines);
    return EXIT_SUCCESS;
}
