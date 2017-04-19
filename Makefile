all:
	if [ ! -d ./bin ]; then mkdir ./bin; fi
	gcc *.c -o ./bin/editor

debug:
	if [ ! -d ./bin ]; then mkdir ./bin; fi
	gcc *.c -g -o ./bin/editor-debug
