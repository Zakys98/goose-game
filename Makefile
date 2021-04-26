cc=gcc
CFLAGS=-std=c11 -pedantic -Wextra -g -Wall
TARGET=goose
SRC_DIR := src
OBJ_DIR := obj
DOC_DIR := doc
OBJS := $(OBJ_DIR)/dialogue.o $(OBJ_DIR)/command.o $(OBJ_DIR)/die.o $(OBJ_DIR)/game_loop.o $(OBJ_DIR)/game_management.o $(OBJ_DIR)/game.o $(OBJ_DIR)/graphic_engine.o $(OBJ_DIR)/object.o $(OBJ_DIR)/player.o $(OBJ_DIR)/screen.o $(OBJ_DIR)/set.o $(OBJ_DIR)/space.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/link.o
TESTS=set_test space_test die_test link_test inventory_test player_test object_test game_management_test

.PHONY: all clean docs test run_tests

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TESTS)

run_tests:
	./set_test
	./space_test
	./die_test
	./inventory_test
	./link_test
	./player_test
	./object_test

set_test: $(OBJ_DIR)/set_test.o $(OBJ_DIR)/set.o
	$(cc) $(CFLAGS) -o set_test $(OBJ_DIR)/set_test.o $(OBJ_DIR)/set.o

die_test: $(OBJ_DIR)/die_test.o $(OBJ_DIR)/die.o
	$(cc) $(CFLAGS) -o die_test $(OBJ_DIR)/die_test.o $(OBJ_DIR)/die.o
	
space_test: $(OBJ_DIR)/space_test.o $(OBJ_DIR)/space.o $(OBJ_DIR)/link.o $(OBJ_DIR)/set.o
	$(cc) $(CFLAGS) -o space_test $(OBJ_DIR)/space_test.o $(OBJ_DIR)/space.o $(OBJ_DIR)/link.o $(OBJ_DIR)/set.o

inventory_test: $(OBJ_DIR)/inventory_test.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/set.o $(OBJ_DIR)/object.o
	$(cc) $(CFLAGS) -o inventory_test $(OBJ_DIR)/inventory_test.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/set.o $(OBJ_DIR)/object.o

link_test: $(OBJ_DIR)/link_test.o $(OBJ_DIR)/link.o
	$(cc) $(CFLAGS) -o link_test $(OBJ_DIR)/link_test.o $(OBJ_DIR)/link.o

player_test: $(OBJ_DIR)/player_test.o $(OBJ_DIR)/player.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/set.o $(OBJ_DIR)/object.o
	$(cc) $(CFLAGS) -o player_test $(OBJ_DIR)/player_test.o $(OBJ_DIR)/player.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/set.o $(OBJ_DIR)/object.o

object_test: $(OBJ_DIR)/object_test.o $(OBJ_DIR)/object.o
	$(cc) $(CFLAGS) -o object_test $(OBJ_DIR)/object_test.o $(OBJ_DIR)/object.o

game_management_test: $(OBJ_DIR)/game_management_test.o $(OBJ_DIR)/command.o $(OBJ_DIR)/die.o $(OBJ_DIR)/game_management.o $(OBJ_DIR)/game.o $(OBJ_DIR)/graphic_engine.o $(OBJ_DIR)/object.o $(OBJ_DIR)/player.o $(OBJ_DIR)/screen.o $(OBJ_DIR)/set.o $(OBJ_DIR)/space.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/link.o
	$(cc) $(CFLAGS) -o game_management_test $(OBJ_DIR)/game_management_test.o $(OBJ_DIR)/die.o $(OBJ_DIR)/command.o $(OBJ_DIR)/game_management.o $(OBJ_DIR)/game.o $(OBJ_DIR)/graphic_engine.o $(OBJ_DIR)/object.o $(OBJ_DIR)/player.o $(OBJ_DIR)/screen.o $(OBJ_DIR)/set.o $(OBJ_DIR)/space.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/link.o

docs: Doxyfile
	doxygen Doxyfile

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET) $(TESTS)
