all:
	if [ ! -d ./bin ]; then mkdir ./bin; fi
	gcc *.c -o ./bin/editor

debug:
	if [ ! -d ./bin ]; then mkdir ./bin; fi
	gcc *.c -g -o ./bin/editor-debug

val:
	make
	valgrind ./bin/editor lib.h

install:
	gcc *.c -o /usr/bin/nw
