#  NW Editor - Super light terminal based editor
#  Copyright (C) 2017 Tyler Steiman
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

## VARIABLES
CC = gcc

CFLAGS = -g -Wall

TARGETS = nw.c \
	dispatch.c \
	line.c \
	screen.c \
	file.c \
	lib.c \
	syn.c \
	opt.c

TARGETS_TEST = $(TARGETS) test/*.c

CC_VARS_TEST = -DNW_TEST_MODE 

BIN = ./bin/

BIN_EX = nw
BIN_TEST = nw-test
BIN_DEBUG = nw-debug

SAVE = $(BIN)/DEBUG

LIBRARIES = -lncurses

DEFAULT_RUN_FILE = lib.h

## FORMULAS
### Default make script for compiling our actual NW editor binary.
all:
	make directories
	$(CC) $(TARGETS) -o $(BIN)$(BIN_EX) $(LIBRARIES)

### Grep all @TODO flags in repo
find-todo:
	grep --color -Rin "@TODO" *

### Remove ./bin directory
clean:
	rm -rf ./bin

### Create ./bin directory if it doesn't exist
directories:
	if [ ! -d ./bin ]; then mkdir ./bin; fi

### Run the editor WITHOUT COMPILING for whatever our default
### run file is defined as
run:
	$(BIN)$(BIN_EX) -f $(SAVE) $(DEFAULT_RUN_FILE)

### Same as run however without specifying a file. This should
### open an empty buffer.
run-new:
	$(BIN)$(BIN_EX) -f $(SAVE)

### Compile for testing. This passes test variables into our binary
### so we can run the test suite. This does not launch the editor except
### for in tests. If this does not work it's because there are some problems
### with Linux with how loadFile is trying to be called again within the test
### suite files.
test-build:
	make directories
	$(CC) $(CC_VARS_TEST) $(TARGETS_TEST) -o $(BIN)$(BIN_TEST) $(LIBRARIES)

### Execute tests after compiling our test binary
tests:
	make test-build
	make run-tests
	make run-tests-new

### Run tests on default run file
run-tests:
	$(BIN)$(BIN_TEST) -f $(SAVE) $(DEFAULT_RUN_FILE)

### Run tests on empty file
run-tests-new:
	$(BIN)$(BIN_TEST) -f $(SAVE)

run-compare:
	make run
	less $(SAVE)

### Compile debug binary with dbg symbols for debugging with GDB
debug:
	make directories
	$(CC) $(TARGETS) -g -o $(BIN)$(BIN_DEBUG) $(LIBRARIES)

### Compile debug symbols & launch gdb
gdb:
	make debug
	gdb $(BIN)$(BIN_DEBUG)

### Symlink our bin/nw binary into /usr/local/bin/nw for use anywhere!
link:
	ln -s $(PWD)/bin/$(BIN_EX) /usr/local/bin/$(BIN_EX)
