cc=gcc
CFLAGS=-std=c11 -Werror -pedantic -Wextra -g -Wall
TARGET=goose
OBJS := command.o die.o game_loop.o game_reader.o game.o graphic_engine.o object.o player.o screen.o set.o space.o

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: set_test
	./set_test

set_test: set_test.o set.o
	$(cc) $(CFLAGS) -o set_test set_test.o set.o

clean:
	rm *.o $(TARGET) set_test
