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

CC = gcc

CFLAGS = -g -Wall

TARGETS = nw.c dispatch.c line.c screen.c  file.c lib.c syn.c opt.c

BIN = ./bin/

BIN_EX = nw
BIN_TEST = nw-test
BIN_DEBUG = nw-debug

all:
	make directories
	$(CC) $(TARGETS) -o $(BIN)$(BIN_EX) -lncurses

find-todo:
	grep --color -Rin "@TODO" *

clean:
	rm -rf ./bin

directories:
	if [ ! -d ./bin ]; then mkdir ./bin; fi

run:
	$(BIN)$(BIN_EX) -f ./bin/DEBUG.c lib.h

run-new:
	$(BIN)$(BIN_EX) -f ./bin/DEBUG-NEW.c

test-build:
	make directories
	$(CC) -DNW_TEST_MODE $(TARGETS) test/*.c -o $(BIN)$(BIN_TEST) -lncurses

tests:
	make test-build
	make run-tests
	make run-tests-new

run-tests:
	$(BIN)$(BIN_TEST) -f ./bin/DEBUG_TEST.c lib.h

run-tests-new:
	$(BIN)$(BIN_TEST) -f ./bin/DEBUG_TEST.c

debug:
	make directories
	$(CC) $(TARGETS) -g -o $(BIN)$(BIN_DEBUG) -lncurses

gdb:
	make debug
	gdb $(BIN)$(BIN_DEBUG)

link:
	ln -s $(PWD)/bin/$(BIN_EX) /usr/local/bin/$(BIN_EX)
