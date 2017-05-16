all:
	make directories
	gcc *.c -o ./bin/editor -lncurses

directories:
	if [ ! -d ./bin ]; then mkdir ./bin; fi

run:
	make
	./bin/editor -f ./bin/DEBUG.c lib.h

run-new:
	make
	./bin/editor -f ./bin/DEBUG.c

run-debug:
	make
	./bin/editor -d -f ./bin/DEBUG.c lib.h

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
	gcc *.c -o /usr/local/bin/nw -lncurses
