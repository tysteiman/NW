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

all:
	make directories
	gcc *.c test/*.c -o ./bin/editor -lncurses

help:
	./bin/editor -?

find-todo:
	grep --color -Rin "@TODO" *

clean:
	rm -rf ./bin

directories:
	if [ ! -d ./bin ]; then mkdir ./bin; fi

run:
	make
	./bin/editor -f ./bin/DEBUG.c lib.h

run-new:
	make
	./bin/editor -f ./bin/DEBUG.c

show:
	less ./bin/DEBUG.c

run-compare:
	make run
	make show

run-new-compare:
	make run-new
	make show

run-debug:
	./bin/editor -d -f ./bin/DEBUG.c lib.h

tests:
	make
	make run-tests
	make run-tests-new

run-tests:
	./bin/editor -t -f ./bin/DEBUG_TEST.c lib.h

run-tests-new:
	./bin/editor -t -f ./bin/DEBUG_TEST.c

run-debug-compare:
	make run-debug
	cat ./bin/DEBUG.c

debug:
	make directories
	gcc *.c -g -o ./bin/editor-debug -lncurses

gdb:
	make debug
	gdb ./bin/editor-debug

val:
	make
	valgrind ./bin/editor -d -f ./bin/DEBUG.c lib.h

install:
	gcc *.c -o /usr/bin/nw
