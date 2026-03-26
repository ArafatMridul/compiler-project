CC=gcc
CFLAGS=-Wall -Wextra -O2

.PHONY: all run clean

all: run

compiler.tab.c compiler.tab.h: compiler.y
	bison -d -o compiler.tab.c compiler.y

compiler.yy.c: compiler.l compiler.tab.h
	flex -o compiler.yy.c compiler.l

translator: compiler.tab.c compiler.yy.c
	$(CC) $(CFLAGS) compiler.tab.c compiler.yy.c -o translator -lfl

output.c: translator input.txt
	./translator input.txt output.c

output: output.c
	$(CC) $(CFLAGS) output.c -o output -lm

run: output
	./output

clean:
	rm -f compiler.tab.c compiler.tab.h compiler.yy.c translator output.c output output.txt