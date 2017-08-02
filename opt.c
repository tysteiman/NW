#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "opt.h"
#include "lib.h"
#include "file.h"

/**
 * Parse all command line options passed to our binary.
 *   d: Debug mode. This will allow our program to run without
 *      using an ncurses window. This will run any test functions
 *      we have written a routine for, and dump the file along
 *      with meta data (cursor, updated file, etc) to stdout.
 *   t: Test mode. This will launch the test suite and give output based
 *      on pass/fail status of that suite.
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

    while ((curOpt = getopt(argc, argv, "dt?f:w:c")) != -1)
        {
            switch (curOpt)
                {
                case 'd':
                    /**
                     * Toggle debug mode (dump file data, etc)
                     */
                    opts.debug = TRUE;
                    break;
                case 't':
                    /**
                     * Toggle test mode (run test suite)
                     */
                     opts.test = TRUE;
                     break;
                case '?':
                    /**
                     * Display command line usage
                     */
                    fprintf(stderr, "USAGE: nw [-option] <file_name>\n");

                    /* -d */
                    colorStr("\t-d", YELLOW);
                    fprintf(stderr, ": Debug Mode\n");
                    
                    /* -t */
                    colorStr("\t-t", YELLOW);
                    fprintf(stderr, ": Run Test Suite\n");

                    /* -f */
                    colorStr("\t-f ", YELLOW);
                    colorStr("FILE", CYAN);
                    fprintf(stderr, ": Set save target. This opens a file and writes output to FILE\n");

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
}
