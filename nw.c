/**
 *   NW Editor - Super light terminal based editor
 *   Copyright (C) 2017 Tyler Steiman
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>

#include "opt.h"
#include "file.h"
#include "screen.h"
#include "dispatch.h"
#include "syn.h"
#include "test/test.h"

int
main(int argc, char **argv)
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
    if (NW_TEST_MODE)
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
                    
                    if (screen.init_screen)
                        {
                            clear();
                            screen.init_screen = FALSE;
                        }

                    /* RESIZE TERMINAL */
                    if (input == KEY_RESIZE)
                        {
                            resizeScreen(&file);
                            continue;
                        }
                        
                    /* NEW LINE */
                    else if (NW_KEY_EQ(NW_KEY_NEW_LINE))
                        {
                            file.edited = TRUE;
                            dispatchNewLine(&file);
                            continue;
                        }

                    /* MOVE RIGHT */
                    else if (NW_KEY_EQ(NW_KEY_RIGHT) || input == KEY_RIGHT)
                        {
                            dispatchRight(&file);
                            continue;
                        }

                    /* MOVE LEFT */
                    else if (NW_KEY_EQ(NW_KEY_LEFT) || input == KEY_LEFT)
                        {
                            dispatchLeft(&file);
                            continue;
                        }

                    /* MOVE DOWN */
                    else if (NW_KEY_EQ(NW_KEY_DOWN) || input == KEY_DOWN)
                        {
                            dispatchDown(&file);
                            continue;
                        }

                    /* MOVE UP */
                    else if (NW_KEY_EQ(NW_KEY_UP) || input == KEY_UP)
                        {
                            dispatchUp(&file);
                            continue;
                        }

                    /* END OF LINE */
                    else if (NW_KEY_EQ(NW_KEY_END) || input == KEY_END)
                        {
                            dispatchEnd(&file);
                            continue;
                        }

                    /* BEGINNING OF LINE */
                    else if (NW_KEY_EQ(NW_KEY_BEG) || input == KEY_HOME)
                        {
                            dispatchBeg(&file);
                            continue;
                        }

                    /* PAGE DOWN */
                    else if (NW_KEY_EQ(NW_KEY_PAGE_DOWN) || input == KEY_NPAGE)
                        {
                            dispatchPageDown(&file);
                            continue;
                        }

                    /* PAGE UP */
                    else if (NW_KEY_EQ(NW_KEY_PAGE_UP) || input == KEY_PPAGE)
                        {
                            dispatchPageUp(&file);
                            continue;
                        }

                    /* BACKSPACE */
                    else if (input == KEY_BACKSPACE || input == NW_KEY_BACKSPACE)
                        {
                            /**
                             * Backspace is essentially the same exact thing as moving left
                             * and deleting, we don't have to make any new functionality for
                             * a proper backspace. Only check if the cursor x is at 0 since we
                             * obviously can't move left at that point.
                             */
                            if (file.cursor.x != 0)
                                {
                                    dispatchLeft(&file);
                                    dispatchDeleteChar(&file);
                                }
                            else
                                {
                                    /**
                                     * When we are at NW_CURX:0 we want to just join the line.
                                     * we could probably have called delete char regardless however
                                     * i think this is a little more straight forward and readable
                                     * with functionaity we already have. Delete char will eval what
                                     * to do but here we already know.
                                     */
                                    dispatchJoinLine(&file);
                                }

                            file.edited = TRUE;

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
                            int res = saveFile(&file);
                            if (res)
                                {
                                    continue;
                                }
                            else
                                {
                                    /**
                                     * When the file is not writable we need to check to
                                     * see if the file was saved or not. This should bomb out
                                     * since in file.c it will see we can't save the file because in
                                     * that instance the file pointer should return NULL.
                                     */
                                    NW_SCR_CLOSE();
                                    printf("ERROR: This file was not able to be saved.\n");
                                    printf("Please ensure you have permissions to edit this file.\n");
                                    break;
                                }
                        }

                    else if (NW_KEY_EQ(NW_KEY_DEL) || input == KEY_DC)
                        {
                            file.edited = TRUE;
                            dispatchDeleteChar(&file);
                            continue;
                        }

                    else if (NW_KEY_EQ(NW_KEY_DEL_LINE))
                        {
                            file.edited = TRUE;
                            dispatchDeleteLine(&file);
                            continue;
                        }

                    else if (NW_KEY_EQ(NW_KEY_JOIN_LINE))
                        {
                            file.edited = TRUE;
                            dispatchJoinLine(&file);
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

                            /* check for RETURN key */
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
                            /* check for TAB key */
                            else if (input == NW_KEY_TAB)
                                {
                                    /* handle TAB key */
                                    int i = 0;
                                    int tabWidth = opts.tabWidth;

                                    /**
                                     * We should be able to handle TAB characters by simply calling our
                                     * dispatch insert on opts.tabWidth for that amount of spaces. By
                                     * default the NW editor will only insert spaces!!
                                     */
                                    for (; i < opts.tabWidth; i++)
                                        {
                                            dispatchInsert(' ', &file);
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
