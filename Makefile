all:
	if [ ! -d ./bin ]; then mkdir ./bin; fi
	gcc *.c -o ./bin/editor -lncurses

debug:
	if [ ! -d ./bin ]; then mkdir ./bin; fi
	gcc *.c -g -o ./bin/editor-debug -lncurses

gdb:
	make debug
	gdb ./bin/editor

val:
	make
	valgrind ./bin/editor lib.h -d

install:
	gcc *.c -o /usr/local/bin/nw -lncurses
