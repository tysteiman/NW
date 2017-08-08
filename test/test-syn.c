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

#include "test.h"
#include "../syn.h"

void
parseFileExtensionTest(file_t *file)
{
    /* rb */
    char *testFile = "/Users/foo/proj/ruby_file.rb";
    char *res = parseExtension(testFile);

    NW_ASSERT_STR(res, "rb", "Extension of ruby_file.rb is rb");

    /* c */
    char *cTest = "~/test.c";
    char *cRes = parseExtension(cTest);

    NW_ASSERT_STR(cRes, "c", "Extension of ~/test.c is c");

    /* sh */
    char *shTest = "~/.file.sh";
    char *shRes = parseExtension(shTest);

    NW_ASSERT_STR(shRes, "sh", "Extension of ~/.file.sh is sh");

    /* yaml */
    char *ymlTest = "/Users/person/proj/apps/rails/config/database.yaml";
    char *ymlRes = parseExtension(ymlTest);

    NW_ASSERT_STR(ymlRes, "yaml", "Extension of ...database.yaml is yaml");
}
