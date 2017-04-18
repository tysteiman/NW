all:
	if [ ! -d ./bin ]; then mkdir ./bin; fi
	gcc *.c -o ./bin/editor
