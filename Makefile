all:
	if [ ! -d ./bin ]; then mkdir ./bin; fi
	gcc *.c -o ./bin/editor -lncurses

run:
	make
	./bin/editor -f ./bin/DEBUG.c lib.h

run-debug:
	make
	./bin/editor -d -f ./bin/DEBUG.c lib.h

run-debug-compare:
	make run-debug
	cat ./bin/DEBUG.c

debug:
	if [ ! -d ./bin ]; then mkdir ./bin; fi
	gcc *.c -g -o ./bin/editor-debug -lncurses

gdb:
	make debug
	gdb ./bin/editor-debug

val:
	make
	valgrind ./bin/editor lib.h -d

install:
	gcc *.c -o /usr/local/bin/nw -lncurses
