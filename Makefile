all:
	if [ ! -d ./bin ]; then mkdir ./bin; fi
	gcc *.c -o ./bin/editor

debug:
	if [ ! -d ./bin ]; then mkdir ./bin; fi
	gcc *.c -g -o ./bin/editor-debug

gdb:
	make debug
	gdb ./bin/editor

val:
	make
	valgrind ./bin/editor lib.h -d

install:
	gcc *.c -o /usr/bin/nw
