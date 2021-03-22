cc=gcc
CFLAGS=-std=c11 -pedantic -Wextra -g -Wall
TARGET=goose
SRC_DIR := src
OBJ_DIR := obj
DOC_DIR := doc
OBJS := $(OBJ_DIR)/command.o $(OBJ_DIR)/die.o $(OBJ_DIR)/game_loop.o $(OBJ_DIR)/game_reader.o $(OBJ_DIR)/game.o $(OBJ_DIR)/graphic_engine.o $(OBJ_DIR)/object.o $(OBJ_DIR)/player.o $(OBJ_DIR)/screen.o $(OBJ_DIR)/set.o $(OBJ_DIR)/space.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/link.o
TESTS=set_test space_test die_test

.PHONY: all clean

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TESTS)
	./set_test
	./space_test
	./die_test

set_test: $(OBJ_DIR)/set_test.o $(OBJ_DIR)/set.o
	$(cc) $(CFLAGS) -o set_test $(OBJ_DIR)/set_test.o $(OBJ_DIR)/set.o

die_test: $(OBJ_DIR)/die_test.o $(OBJ_DIR)/die.o
	$(cc) $(CFLAGS) -o die_test $(OBJ_DIR)/die_test.o $(OBJ_DIR)/die.o
	
space_test: $(OBJ_DIR)/space_test.o $(OBJ_DIR)/space.o $(OBJ_DIR)/set.o
	$(cc) $(CFLAGS) -o space_test $(OBJ_DIR)/space_test.o $(OBJ_DIR)/space.o $(OBJ_DIR)/set.o

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET) $(TESTS)
