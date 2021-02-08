CFLAGS= -ansi -Werror -pedantic -Wextra -g -Wall

all: main

main: game_loop.o
	gcc $(CFLAGS) game_loop.o -o main

game_loop.o: game_loop.c
	gcc $(CFLAGS) -c game_loop.c -o game_loop.o

clean:
	rm *.o main
