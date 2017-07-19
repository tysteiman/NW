all:
	make directories
	gcc *.c test/*.c -o ./bin/editor

help:
	./bin/editor -?

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
	make
	./bin/editor -d -f ./bin/DEBUG.c lib.h

run-test:
	make
	./bin/editor -t -f ./bin/DEBUG_TEST.c lib.h

run-test-new:
	make
	./bin/editor -t -f ./bin/DEBUG_TEST.c

run-debug-compare:
	make run-debug
	cat ./bin/DEBUG.c

debug:
	make directories
	gcc *.c -g -o ./bin/editor-debug

gdb:
	make debug
	gdb ./bin/editor-debug

val:
	make
	valgrind ./bin/editor -d -f ./bin/DEBUG.c lib.h

install:
	gcc *.c -o /usr/bin/nw
