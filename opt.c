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

#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "opt.h"
#include "lib.h"
#include "file.h"

/**
 * Parse all command line options passed to our binary.
 *   w: Tab width. Defaults to 4 however can be set to anything. This is
 *      how many spaces will be entered into the buffer upon pressing TAB
 *   ?: This simply shows the proper syntax for opening NW. This
 *      does not show all possible command line arguments but maybe
 *      should have that functionality in the future.
 *   f: This requires an argument and sets the fileSaveTarget. This
 *      signifies our target save file when performing save. This is
 *      used for copying a file into a new file directly. In other words
 *      if we want to copy a certain file but do immediately via opening
 *      our editor, you can type nw lib.h -f lib2.h, edit the file, and
 *      save into a new file called lib2.h.
 */
void
parseOpts(int argc, char **argv)
{
    /**
     * Current option we use to run through our switch statement.
     */
    int curOpt;

    while ((curOpt = getopt(argc, argv, "?f:w:c")) != -1)
        {
            switch (curOpt)
                {
                case '?':
                    /**
                     * Display command line usage
                     */
                    fprintf(stderr, "USAGE: nw [-option] <file_name>\n");

                    /* -f */
                    colorStr("\t-f ", YELLOW);
                    colorStr("FILE", CYAN);
                    fprintf(stderr, ": Set save target. This opens a file and writes output to FILE\n");
                    
                    colorStr("\t-w ", YELLOW);
                    colorStr("WIDTH", CYAN);
                    fprintf(stderr, ": Set tab width. This amount of spaces will be entered upon pressing TAB\n");

                    exit(EXIT_SUCCESS);
                case 'f':
                    /**
                     * Change our file target for copying to a new file
                     * upon saving.
                     */
                    opts.fileSaveTarget = optarg;
                    break;
                case 'w':
                    /**
                     * set tab with
                     */
                    opts.tabWidth = atoi(optarg);
                    break;
                default:
                    err("Invalid argument.");
                }
        }

    opts.fileName = argv[optind] ? argv[optind] : NW_EMPTY_FILE;

    /**
     * If we haven't received a -f flag we use opts.fileName as our
     * save target for obvious reasons.
     */
    if (!opts.fileSaveTarget)
        {
            opts.fileSaveTarget = opts.fileName;
        }

    if (!opts.tabWidth)
        {
            opts.tabWidth = 4;
        }
}
