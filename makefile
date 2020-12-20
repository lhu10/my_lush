all: lush.o lush_helper.o parse.o
	gcc -o lush lush.o lush_helper.o parse.o

lush.o: lush.c parse.c 
	gcc -c lush.c

lush_helper.o: lush_helper.c lush_helper.h parse.h
	gcc -c lush_helper.c

parse.o: parse.c parse.h
	gcc -c parse.c

run: 
	./lush
