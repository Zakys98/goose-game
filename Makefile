cc=gcc
CFLAGS=-std=c11 -pedantic -Wextra -g -Wall
TARGET=goose
OBJS := command.o die.o game_loop.o game_reader.o game.o graphic_engine.o object.o player.o screen.o set.o space.o
TESTS=set_test space_test die_test

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TESTS)
	./set_test
	./space_test
	./die_test

set_test: set_test.o set.o
	$(cc) $(CFLAGS) -o set_test set_test.o set.o

die_test: die_test.o die.o
	$(cc) $(CFLAGS) -o die_test die_test.o die.o
	
space_test: space_test.o space.o set.o
	$(cc) $(CFLAGS) -o space_test space_test.o space.o set.o

clean:
	rm *.o $(TARGET) $(TESTS)
