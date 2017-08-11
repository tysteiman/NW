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
	gcc nw.c dispatch.c line.c screen.c  file.c lib.c syn.c opt.c -o ./bin/nw -lncurses

find-todo:
	grep --color -Rin "@TODO" *

clean:
	rm -rf ./bin

directories:
	if [ ! -d ./bin ]; then mkdir ./bin; fi

run:
	./bin/nw -f ./bin/DEBUG.c lib.h

run-new:
	./bin/nw -f ./bin/DEBUG-NEW.c

test-build:
	make directories
	gcc -DNW_TEST_MODE *.c test/*.c -o ./bin/nw-test -lncurses

tests:
	make test-build
	make run-tests
	make run-tests-new

run-tests:
	./bin/nw-test -f ./bin/DEBUG_TEST.c lib.h

run-tests-new:
	./bin/nw-test -f ./bin/DEBUG_TEST.c

debug:
	make directories
	gcc nw.c dispatch.c line.c screen.c  file.c lib.c syn.c opt.c -g -o ./bin/nw-debug -lncurses

gdb:
	make debug
	gdb ./bin/nw-debug

link:
	ln -s $(PWD)/bin/nw /usr/local/bin/nw
