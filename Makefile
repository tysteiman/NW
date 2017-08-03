all:
	make directories
	gcc *.c test/*.c -o ./bin/editor -lncurses

help:
	./bin/editor -?

find-todo:
	grep --color -Rin "@TODO" * .

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
