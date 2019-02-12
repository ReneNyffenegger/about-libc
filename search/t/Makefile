all: example-glibc example-tq84
	valgrind --leak-check=full example-tq84

example-glibc: prog-glibc.o
	gcc  -g prog-glibc.o -o example-glibc

example-tq84: prog-tq84.o tq84-tsearch.o
	gcc  -g prog-tq84.o tq84-tsearch.o -o example-tq84

prog-glibc.o: prog.c
	gcc -DTQ84_USE_GLIBC -g -c prog.c -o prog-glibc.o

prog-tq84.o: prog.c
	gcc -g -c prog.c -o prog-tq84.o

tq84-tsearch.o: tq84-tsearch.c
	gcc -g -c tq84-tsearch.c -o tq84-tsearch.o
